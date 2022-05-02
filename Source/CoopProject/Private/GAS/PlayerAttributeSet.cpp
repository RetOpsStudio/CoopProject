// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/PlayerAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UPlayerAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, TestVar, COND_None, REPNOTIFY_Always);
}

void UPlayerAttributeSet::OnRep_TestVar(const FGameplayAttributeData& OldTestVar)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, TestVar, OldTestVar);
}
