// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GAUseWithAim.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "Items/ItemBase.h"
#include "../PlayerCharacter.h"

void UGAUseWithAim::TraceForHits(const FGameplayAbilityActorInfo* ActorInfo, TArray<FHitResult>& outHits)
{
	auto actor = Cast<APlayerCharacter>(ActorInfo->OwnerActor);

	TArray<TEnumAsByte<EObjectTypeQuery> > objectTypes{
		UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic),
	};

	const FVector& heightVector = actor->GetActorUpVector();
	const FVector extendHeight = heightVector * m_height;

	const FVector& forwardVect = actor->GetActorForwardVector();

	FVector location = actor->GetActorLocation();

	const FVector centerPoint = location + heightVector * m_centerHeight;
	FVector grabberDirection = centerPoint - actor->GetCameraLocation();
	grabberDirection.Normalize();

	location += grabberDirection * m_forwardOffset;


	UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), (location - extendHeight / 2), (location + extendHeight / 2), m_radius, objectTypes, false, {}, m_bDrawDebug ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None, outHits, true);
}