// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Activators/AItemActivatorBase.h"
#include "Items/Recivers/TTReciverBase.h"
#include "Items/ActivatorUsable.h"
#include "AbilitySystemInterface.h"
#include "GAS/CoopAbilitySystemComponent.h"


void AItemActivatorBase::Use(const FGameplayAbilityActorInfo& usingActorInfo)
{
	//if (!HasAuthority())
	//{
	//	return;
	//}
	UseItem(usingActorInfo);
}
void AItemActivatorBase::StopUsing(const FGameplayAbilityActorInfo& usingActorInfo)
{
	//if (!HasAuthority())
	//{
	//	return;
	//}
	StopUsingItem(usingActorInfo);
}
//CHECK FOR NULLPTR's
void AItemActivatorBase::UseItem(const FGameplayAbilityActorInfo& usingActorInfo) //put this on interface, add 2 interfaces or "usable by player"
{
	Super::UseItem(usingActorInfo);
	IActivatorUsable* reciver = Cast<IActivatorUsable>(m_reciver);
	if (reciver)
	{
		reciver->Use(usingActorInfo);
	}

	ApplyGameplayEffectOnUsingActor(usingActorInfo);
	
}
void AItemActivatorBase::StopUsingItem(const FGameplayAbilityActorInfo& usingActorInfo)
{
	//if (!HasAuthority())
	//{
	//	return;
	//}
	
	IActivatorUsable* reciver = Cast<IActivatorUsable>(m_reciver);
	if (reciver)
	{
		reciver->StopUsing(usingActorInfo);
	}
	//PutGameplayEffectOnUsingActor(usingActorInfo);
	Super::StopUsingItem(usingActorInfo);
}



void AItemActivatorBase::ApplyGameplayEffectOnUsingActor(const FGameplayAbilityActorInfo& usingActorInfo)
{
	if (!IsValid(m_effectToApply))
	{
		return;
	}

	TWeakObjectPtr<UAbilitySystemComponent> ASC = usingActorInfo.AbilitySystemComponent;

	if (!IsValid(ASC.Get()))
	{
		return;
	}

	FGameplayEffectContextHandle effectContext = ASC->MakeEffectContext();
	effectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle specHandle = ASC->MakeOutgoingSpec(m_effectToApply, 1, effectContext);

	if (specHandle.IsValid())
	{
		ASC->ApplyGameplayEffectSpecToSelf(*specHandle.Data.Get());
	}
}