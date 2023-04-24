// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActivatorUsable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UActivatorUsable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COOPPROJECT_API IActivatorUsable
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void Use(const struct FGameplayAbilityActorInfo& usingActorInfo) = 0;

	UFUNCTION()
	virtual void StopUsing(const struct FGameplayAbilityActorInfo& usingActorInfo) = 0;
};
