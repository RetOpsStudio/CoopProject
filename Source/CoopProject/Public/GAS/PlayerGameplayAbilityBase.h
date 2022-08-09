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
protected:
	/*Called when attribute is granted to Actor, mostly used in case of granting ability via gameplay effect*/
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	EAbilityInputID AbilityInputID = EAbilityInputID::None;

	/*if ability should be played or not right after granting*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	bool bActivateAbilityOnSet = false;
};
