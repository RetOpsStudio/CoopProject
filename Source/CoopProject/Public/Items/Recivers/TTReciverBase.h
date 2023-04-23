// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "TTReciverBase.generated.h"

/**
 * 
 */
UCLASS()
class COOPPROJECT_API ATTReciverBase : public AItemBase
{
	GENERATED_BODY()

public:
	virtual void UseItem(const FGameplayAbilityActorInfo& usingActorInfo) override;

	virtual void StopUsingItem(const FGameplayAbilityActorInfo& usingActorInfo) override;
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	int m_activatorsThreshold = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	int m_currentActivators = 0;

	//to enforce that item will be/stop being used once
	bool m_bItemInUse = false; 


};
