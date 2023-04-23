// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Recivers/TTReciverBase.h"

void ATTReciverBase::UseItem(const FGameplayAbilityActorInfo& usingActorInfo)
{
	if (!HasAuthority())
	{
		return;
	}

	if (++m_currentActivators < m_activatorsThreshold || m_bItemInUse)
	{
		return;
	}

	m_bItemInUse = true; //use item once
	Super::UseItem(usingActorInfo);
}

void ATTReciverBase::StopUsingItem(const FGameplayAbilityActorInfo& usingActorInfo)
{
	if (!HasAuthority())
	{
		return;
	}

	if (m_currentActivators > 0)
	{
		m_currentActivators--;
	}
	
	if (m_currentActivators < m_activatorsThreshold && m_bItemInUse) //stop using item once
	{
		m_bItemInUse = false;
		Super::StopUsingItem(usingActorInfo);
	}
}
