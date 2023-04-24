// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Recivers/TTReciverBase.h"

void ATTReciverBase::Use(const FGameplayAbilityActorInfo& usingActorInfo)
{
	if (!HasAuthority())
	{
		return;
	}
	UseItem(usingActorInfo);
}

void ATTReciverBase::StopUsing(const FGameplayAbilityActorInfo& usingActorInfo)
{
	if (!HasAuthority())
	{
		return;
	}
	StopUsingItem(usingActorInfo);
}

void ATTReciverBase::UseItem(const FGameplayAbilityActorInfo& usingActorInfo)
{

	++m_currentActivators;
	//event here to inform how many activators already

	if (m_currentActivators < m_activatorsThreshold)
	{
		return;
	}

	if (m_bItemInUse)
	{
		return;
	}

	m_bItemInUse = true; //use item once

	Super::UseItem(usingActorInfo);
}

void ATTReciverBase::StopUsingItem(const FGameplayAbilityActorInfo& usingActorInfo)
{

	if (ensure(m_currentActivators > 0)) //event on change using actors
	{
		m_currentActivators--;
		//here
	}
	
	if (m_currentActivators < m_activatorsThreshold && m_bItemInUse) //stop using item once
	{
		m_bItemInUse = false;
		Super::StopUsingItem(usingActorInfo);
	}
}
