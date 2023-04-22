// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ItemBase.h"
#include "AItemActivatorBase.generated.h"

/**
 * 
 */
UCLASS()
class COOPPROJECT_API AItemActivatorBase : public AItemBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void PutGameplayEffectOnUsingActor(const FGameplayAbilityActorInfo& usingActorInfo);

	virtual void UseItem(const FGameplayAbilityActorInfo& usingActorInfo) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> m_effectToApply;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reciver")
	AActor* m_reciver = nullptr;

};
