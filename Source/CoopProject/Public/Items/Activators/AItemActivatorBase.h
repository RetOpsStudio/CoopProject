// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ItemBase.h"
#include "../CharacterUsable.h"
#include "AItemActivatorBase.generated.h"
/**
 * 
 */
UCLASS()
class COOPPROJECT_API AItemActivatorBase : public AItemBase, public ICharacterUsable
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void ApplyGameplayEffectOnUsingActor(const FGameplayAbilityActorInfo& usingActorInfo);

	virtual void UseItem(const FGameplayAbilityActorInfo& usingActorInfo) override;

	virtual void StopUsingItem(const FGameplayAbilityActorInfo& usingActorInfo) override;

	//UCharacterUsable
	virtual void Use(const struct FGameplayAbilityActorInfo& usingActorInfo) override;
	virtual void StopUsing(const struct FGameplayAbilityActorInfo& usingActorInfo) override;
	//~UCharaterUsable
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> m_effectToApply;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reciver")
	TArray<AActor*> m_recivers;; //reciver should be an array

};
