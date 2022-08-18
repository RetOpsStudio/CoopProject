// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/ItemBase.h"
#include "AbilitySystemInterface.h"
#include "Components/BoxComponent.h"
#include "GAS/CoopAbilitySystemComponent.h"
#include "GameplayEffects/GEButtonPressed.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();	
}

void AItemBase::UseItem(const FGameplayAbilityActorInfo& usingActorInfo)
{
	if (!HasAuthority())
	{
		return;
	}

	PutGameplayEffectOnUsingActor(usingActorInfo);
	OnItemBeginActivate();
}
void AItemBase::PutGameplayEffectOnUsingActor(const FGameplayAbilityActorInfo& usingActorInfo)
{
	if (!IsValid(m_effectToApply))
	{
		return;
	}
	auto ASC = usingActorInfo.AbilitySystemComponent;

	FGameplayEffectContextHandle effectContext = ASC->MakeEffectContext();
	effectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle specHandle = ASC->MakeOutgoingSpec(m_effectToApply, 1, effectContext);
	if (specHandle.IsValid())
	{
		ASC->ApplyGameplayEffectSpecToSelf(*specHandle.Data.Get());
	}
}
void AItemBase::OnItemBeginActivate()
{
	OnItemBeginActivateBP();
}

void AItemBase::OnItemCancelActivate()
{
	
}


void AItemBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}



