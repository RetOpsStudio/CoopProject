// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterUsable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCharacterUsable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COOPPROJECT_API ICharacterUsable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual void Use(const struct FGameplayAbilityActorInfo& usingActorInfo) = 0;

	UFUNCTION()
	virtual void StopUsing(const struct FGameplayAbilityActorInfo& usingActorInfo) = 0;
};
