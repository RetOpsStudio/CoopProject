// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CoopProject/CoopProject.h"
#include "PlayerGameplayAbilityBase.generated.h"

/**
 * Base for player abilities, has input
 */
UCLASS()
class COOPPROJECT_API UPlayerGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UPlayerGameplayAbilityBase();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	EAbilityInputID AbilityInputID = EAbilityInputID::None;
};
