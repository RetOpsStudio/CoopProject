// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Activators/AItemActivatorBase.h"
#include "Items/Recivers/TTReciverBase.h"

#include "AbilitySystemInterface.h"
//#include "Components/BoxComponent.h"
#include "GAS/CoopAbilitySystemComponent.h"
//#include "GameplayEffects/GEButtonPressed.h"

void AItemActivatorBase::UseItem(const FGameplayAbilityActorInfo& usingActorInfo)
{
	if (!HasAuthority())
	{
		return;
	}
	if (IsValid(m_reciver))
	{
		m_reciver->UseItem(usingActorInfo);
	}
	PutGameplayEffectOnUsingActor(usingActorInfo);
	Super::UseItem(usingActorInfo);
}
void AItemActivatorBase::StopUsingItem(const FGameplayAbilityActorInfo& usingActorInfo)
{
	if (!HasAuthority())
	{
		return;
	}
	if (IsValid(m_reciver))
	{
		m_reciver->StopUsingItem(usingActorInfo);
	}
	//PutGameplayEffectOnUsingActor(usingActorInfo);
	Super::StopUsingItem(usingActorInfo);
}

void AItemActivatorBase::PutGameplayEffectOnUsingActor(const FGameplayAbilityActorInfo& usingActorInfo)
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