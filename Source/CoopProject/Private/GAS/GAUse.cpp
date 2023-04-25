// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GAUse.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Items/CharacterUsable.h"


UGAUse::UGAUse() : Super()
{
	AbilityInputID = EAbilityInputID::Use;
}

void UGAUse::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	GrabberPrototype_InFrontOfActor(ActorInfo);
	if (UAbilityTask_WaitInputRelease* WaitInputReleaseTask = UAbilityTask_WaitInputRelease::WaitInputRelease(this, true))
	{
		WaitInputReleaseTask->OnRelease.AddDynamic(this, &UGAUse::EndAbility);
		WaitInputReleaseTask->ReadyForActivation();
	}
}

void UGAUse::GrabberPrototype_InFrontOfActor(const FGameplayAbilityActorInfo* ActorInfo)
{
	TArray< FHitResult > outHits;
	TraceForHits(ActorInfo, outHits);

	//TODO fix this, to calculate distance to Actor
	outHits.Sort([](const auto& left, const auto& right)
		{
			return left.Distance < right.Distance;
		});

	//Get closest item
	for (const auto& hit : outHits)
	{
		m_itemToUse = Cast<ICharacterUsable>(hit.GetActor());
		if (m_itemToUse)
		{
			m_itemToUse->Use(*ActorInfo);
			break;
		}
	}
}
void UGAUse::TraceForHits(const FGameplayAbilityActorInfo* ActorInfo, TArray<FHitResult>& outHits)
{
	auto actor = ActorInfo->OwnerActor;

	TArray<TEnumAsByte<EObjectTypeQuery> > objectTypes{
		UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic),
	};

	const FVector& heightVector = actor->GetActorUpVector();
	const FVector extendHeight = heightVector * m_height;

	const FVector& forwardVect = actor->GetActorForwardVector();

	auto location = actor->GetActorLocation();
	location += forwardVect * m_forwardOffset;

	const FVector centerPoint = location + heightVector * m_centerHeight;

	UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), centerPoint - extendHeight / 2, centerPoint + extendHeight / 2, m_radius, objectTypes, false, {}, m_bDrawDebug ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None, outHits, true);
}


void UGAUse::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled) ;
	if (m_itemToUse)
	{
		m_itemToUse->StopUsing(*ActorInfo);
		m_itemToUse = nullptr;
	}
}

void UGAUse::EndAbility(float timeHeld)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
