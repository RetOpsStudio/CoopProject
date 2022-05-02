// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/ATPlayMontageAndWaitForEvent.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystemComponent.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/Character.h"

UATPlayMontageAndWaitForEvent::UATPlayMontageAndWaitForEvent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Rate = 1.0f;
	bStopWhenAbilityEnds = true;
}

void UATPlayMontageAndWaitForEvent::Activate()
{
	if (Ability == nullptr)
	{
		return;
	}

	bool bPlayedMontage = false;
	UCoopAbilitySystemComponent* CoopAbilitySystemComponent = GetTargetASC();

	if (IsValid(CoopAbilitySystemComponent))
	{
		const FGameplayAbilityActorInfo* actorInfo = Ability->GetCurrentActorInfo();
		UAnimInstance* animInstance = actorInfo->GetAnimInstance();

		if (IsValid(animInstance))
		{
			EventHandle = CoopAbilitySystemComponent->AddGameplayEventTagContainerDelegate(EventTags, FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &UATPlayMontageAndWaitForEvent::OnGameplayEvent));

			if (CoopAbilitySystemComponent->PlayMontage(Ability, Ability->GetCurrentActivationInfo(), MontageToPlay, Rate, StartSection) > 0.0f)
			{
				if (!ShouldBroadcastAbilityTaskDelegates())
				{
					return;
				}

				CancelledHandle = Ability->OnGameplayAbilityCancelled.AddUObject(this, &UATPlayMontageAndWaitForEvent::OnAbilityCancelled);

				BlendingOutDelegate.BindUObject(this, &UATPlayMontageAndWaitForEvent::OnMontageBlendingOut);
				animInstance->Montage_SetBlendingOutDelegate(BlendingOutDelegate, MontageToPlay);

				MontageEndedDelegate.BindUObject(this, &UATPlayMontageAndWaitForEvent::OnMontageEnded);
				animInstance->Montage_SetEndDelegate(MontageEndedDelegate, MontageToPlay);

				ACharacter* character = Cast<ACharacter>(GetAvatarActor());
				if (character && (character->GetLocalRole() == ROLE_Authority || (character->GetLocalRole() == ROLE_AutonomousProxy && Ability->GetNetExecutionPolicy() == EGameplayAbilityNetExecutionPolicy::LocalPredicted)))
				{
					character->SetAnimRootMotionTranslationScale(AnimRootMotionTranslationScale);
				}

				bPlayedMontage = true;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("UATPlayMontageAndWaitForEvent call to PlayMontage failed"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UATPlayMontageAndWaitForEvent called on invalid AbilitySystemComponent"));
	}

	if (!bPlayedMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("UATPlayMontageAndWaitForEvent called in Ability %s failed to play montage %s; Task Instance Name %s."), *Ability->GetName(), *GetNameSafe(MontageToPlay), *InstanceName.ToString());
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnCancelled.Broadcast(FGameplayTag(), FGameplayEventData());
		}
	}

	SetWaitingOnAvatar();
}

void UATPlayMontageAndWaitForEvent::ExternalCancel()
{
	check(AbilitySystemComponent);

	OnAbilityCancelled();
	
	Super::ExternalCancel();
}

FString UATPlayMontageAndWaitForEvent::GetDebugString() const
{
	UAnimMontage* playingMontage = nullptr;
	if (IsValid(Ability))
	{
		const FGameplayAbilityActorInfo* actorInfo = Ability->GetCurrentActorInfo();
		UAnimInstance* animInstance = actorInfo->GetAnimInstance();

		if (animInstance != nullptr)
		{
			playingMontage = animInstance->Montage_IsActive(MontageToPlay) ? MontageToPlay : animInstance->GetCurrentActiveMontage();
		}
	}

	return FString::Printf(TEXT("PlayMontageAndWaitForEvent. MontageToPlay: %s  (Currently Playing): %s"), *GetNameSafe(MontageToPlay), *GetNameSafe(playingMontage));
}

void UATPlayMontageAndWaitForEvent::OnDestroy(bool AbilityEnded)
{
	if (IsValid(Ability))
	{
		Ability->OnGameplayAbilityCancelled.Remove(CancelledHandle);
		if (AbilityEnded && bStopWhenAbilityEnds)
		{
			StopPlayingMontage();
		}
	}

	UCoopAbilitySystemComponent* coopAbilitySystemComponent = GetTargetASC();
	if (IsValid(coopAbilitySystemComponent))
	{
		coopAbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(EventTags, EventHandle);
	}
	
	Super::OnDestroy(AbilityEnded);
}

UATPlayMontageAndWaitForEvent* UATPlayMontageAndWaitForEvent::PlayMontageAndWaitForEvent(
	UGameplayAbility* OwningAbility, FName TaskInstanceName, UAnimMontage* MontageToPlay,
	FGameplayTagContainer EventTags, float Rate, FName StartSection, bool bStopWhenAbilityEnds,
	float AnimRootMotionTranslationScale)
{
	UAbilitySystemGlobals::NonShipping_ApplyGlobalAbilityScaler_Rate(Rate);

	UATPlayMontageAndWaitForEvent* myObject = NewAbilityTask<UATPlayMontageAndWaitForEvent>(OwningAbility, TaskInstanceName);
	myObject->MontageToPlay = MontageToPlay;
	myObject->EventTags = EventTags;
	myObject->Rate = Rate;
	myObject->StartSection = StartSection;
	myObject->AnimRootMotionTranslationScale = AnimRootMotionTranslationScale;
	myObject->bStopWhenAbilityEnds = bStopWhenAbilityEnds;

	return myObject;
}

bool UATPlayMontageAndWaitForEvent::StopPlayingMontage()
{
	const FGameplayAbilityActorInfo* actorInfo = Ability->GetCurrentActorInfo();
	if (!actorInfo)
	{
		return false;
	}

	UAnimInstance* animInstance = actorInfo->GetAnimInstance();
	if (!IsValid(animInstance))
	{
		return false;
	}

	if (IsValid(AbilitySystemComponent) && IsValid(Ability))
	{
		if (AbilitySystemComponent->GetAnimatingAbility() == Ability && AbilitySystemComponent->GetCurrentMontage() == MontageToPlay)
		{
			FAnimMontageInstance* montageInstance = animInstance->GetActiveInstanceForMontage(MontageToPlay);
			if (IsValid(MontageToPlay))
			{
				montageInstance->OnMontageBlendingOutStarted.Unbind();
				montageInstance->OnMontageEnded.Unbind();
			}

			AbilitySystemComponent->CurrentMontageStop();
			return true;
		}
	}

	return false;
}

UCoopAbilitySystemComponent* UATPlayMontageAndWaitForEvent::GetTargetASC()
{
		return Cast<UCoopAbilitySystemComponent>(AbilitySystemComponent);
}

void UATPlayMontageAndWaitForEvent::OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted)
{
	if (IsValid(Ability) && Ability->GetCurrentMontage() == MontageToPlay)
	{
		if (Montage == MontageToPlay)
		{
			AbilitySystemComponent->ClearAnimatingAbility(Ability);

			ACharacter* character = Cast<ACharacter>(GetAvatarActor());
			if (IsValid(character) && (character->GetLocalRole() == ROLE_Authority || (character->GetLocalRole() == ROLE_AutonomousProxy && Ability->GetNetExecutionPolicy() == EGameplayAbilityNetExecutionPolicy::LocalPredicted)))
			{
				character->SetAnimRootMotionTranslationScale(1.0f);
			}
		}
	}

	if (!ShouldBroadcastAbilityTaskDelegates())
	{
		return;
	}
	
	if (bInterrupted)
	{
		OnInterrupted.Broadcast(FGameplayTag(), FGameplayEventData());
	}
	else
	{
		OnBlendOut.Broadcast(FGameplayTag(), FGameplayEventData());
	}
}

void UATPlayMontageAndWaitForEvent::OnAbilityCancelled()
{
	if (StopPlayingMontage())
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnCancelled.Broadcast(FGameplayTag(), FGameplayEventData());
		}
	}
}

void UATPlayMontageAndWaitForEvent::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (!bInterrupted)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnCompleted.Broadcast(FGameplayTag(), FGameplayEventData());
		}
	}

	EndTask();
}

void UATPlayMontageAndWaitForEvent::OnGameplayEvent(FGameplayTag EventTag,
                                                    const FGameplayEventData* Payload)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		FGameplayEventData tempData = *Payload;
		tempData.EventTag = EventTag;

		EventReceived.Broadcast(EventTag, tempData);
	}
}
