// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Recivers/TTReciverBase.h"
#include "TTDoors.generated.h"

/**
 * 
 */
UCLASS()
class COOPPROJECT_API ATTDoors : public ATTReciverBase
{
	GENERATED_BODY()
	virtual void StopUsingItem(const FGameplayAbilityActorInfo& usingActorInfo) override;
};
