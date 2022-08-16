// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GAUse.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "Items/ItemBase.h"
#include <algorithm>

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
	//TODO refactor this, cause now its only prototype
	auto actor = ActorInfo->OwnerActor;
	auto location = actor->GetActorLocation();
	FVector forwardVect = actor->GetActorForwardVector();
	//add forward offset
	location += forwardVect * m_forwardOffset;
	FVector heightVector = FVector::UnitZ() -  UKismetMathLibrary::ProjectVectorOnToVector(FVector::UnitZ(), forwardVect);
	//should be normalized anyway but...
	heightVector.Normalize();

	TArray<TEnumAsByte<EObjectTypeQuery> > ObjectTypes{
		UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic),
	};

	FVector extendHeight = heightVector * m_height;
	FVector centerPoint = location + heightVector * m_centerHeight;

	TArray< FHitResult > outHits;
	UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), centerPoint - extendHeight/2, centerPoint - extendHeight/2, m_radius, ObjectTypes, false, {}, m_bDrawDebug ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None, outHits, true);

	if (!outHits.IsEmpty())
	{
		//TODO life quality - implement std::min_element in some library
		//find closest Hit
		AItemBase* closestItem = nullptr;

		double minDist = DBL_MAX;
		for (int i = 0; i < outHits.Num();i++)
		{
			auto& hit = outHits[i];

			AItemBase* itemHitted = Cast<AItemBase>((hit).GetActor());
			if (IsValid(itemHitted) && outHits[i].Distance < minDist)
			{
				closestItem = itemHitted;
				minDist = hit.Distance;
			}
		}

		if (IsValid(closestItem))
		{
			closestItem->UseItem(*ActorInfo);
		}

		UE_LOG(LogTemp, Log, TEXT("hitted actor %s."), *closestItem->GetName());
	}
}
void UGAUse::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}