// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GAUse.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h"
#include "Items/ItemBase.h"

UGAUse::UGAUse() : Super()
{
	AbilityInputID = EAbilityInputID::Use;
}

void UGAUse::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//TODO refactor this, cause now its only prototype
	auto location = ActorInfo->OwnerActor->GetActorLocation();
	TArray<TEnumAsByte<EObjectTypeQuery> > ObjectTypes{ 
		UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic),
	};
	TArray< FHitResult > OutHits;
	UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), location - FVector(0, 0, 40), location + FVector(0, 0, 40), 50, ObjectTypes, false, {}, EDrawDebugTrace::Persistent, OutHits, true);

	for (const auto& hit : OutHits)
	{
		AItemBase* itemHitted = Cast<AItemBase>(hit.GetActor());
		if (IsValid(itemHitted))
		{
			
			itemHitted->UseItem(*ActorInfo);
			break;
		}
		UE_LOG(LogTemp, Log, TEXT("hitted actor %s."), *hit.ToString());
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UGAUse::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}