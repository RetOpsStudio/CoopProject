// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GAUse.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "Items/ItemBase.h"

UGAUse::UGAUse() : Super()
{
	AbilityInputID = EAbilityInputID::Use;
}

void UGAUse::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	GrabberPrototype_InFrontOfActor(ActorInfo);

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
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
		AItemBase* itemHitted = Cast<AItemBase>((hit).GetActor());
		if (IsValid(itemHitted))
		{
			itemHitted->UseItem(*ActorInfo);
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
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}