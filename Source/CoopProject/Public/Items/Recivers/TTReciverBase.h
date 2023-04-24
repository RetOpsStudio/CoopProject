// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "../ActivatorUsable.h"
#include "TTReciverBase.generated.h"

/**
 * 
 */
UCLASS()
class COOPPROJECT_API ATTReciverBase : public AItemBase, public IActivatorUsable
{
	GENERATED_BODY()

public:
	//IActivatorUsable
	virtual void Use(const FGameplayAbilityActorInfo& usingActorInfo) override;

	virtual void StopUsing(const FGameplayAbilityActorInfo& usingActorInfo) override;
	//~IActivatorUsable

	virtual void UseItem(const FGameplayAbilityActorInfo& usingActorInfo) override;

	virtual void StopUsingItem(const FGameplayAbilityActorInfo& usingActorInfo) override;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	int32 m_activatorsThreshold = 1;

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	int32 m_currentActivators = 0;

	//to enforce that item will be/stop being used once
	bool m_bItemInUse = false; 


};
