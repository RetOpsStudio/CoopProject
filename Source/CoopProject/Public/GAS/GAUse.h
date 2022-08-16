// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/PlayerGameplayAbilityBase.h"
#include "GAUse.generated.h"

/**
 * 
 */
UCLASS()
class COOPPROJECT_API UGAUse : public UPlayerGameplayAbilityBase
{
	GENERATED_BODY()
public:
	UGAUse();

protected:
	virtual void GrabberPrototype_InFrontOfActor(const FGameplayAbilityActorInfo* ActorInfo);
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	//TODO find sensible default values
	//how much center will be rised comparing to actor location
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	double m_centerHeight = 0;
	//how much center will be pushed frontward/backward of actor
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	double m_forwardOffset = 0;
	//radius of sphere
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	double m_radius = 0;
	//height of sphere
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	double m_height = 0;
	//draw debug?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	double m_bDrawDebug = true;
};
