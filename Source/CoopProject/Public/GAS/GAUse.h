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

	/*Override this in child classes to implement other types of trace*/
	virtual void TraceForHits(const FGameplayAbilityActorInfo* ActorInfo, TArray<FHitResult>& outHits);

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	UFUNCTION()
	void EndAbility(float timeHeld);
protected:
	//how much center will be rised comparing to actor location
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	double m_centerHeight = 0.f;
	//how much center will be pushed frontward/backward of actor
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	double m_forwardOffset = 50.f;
	//radius of sphere
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	double m_radius = 50.f;
	//height of sphere
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	double m_height = 100.f;
	//draw debug?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	double m_bDrawDebug = true;

	class ICharacterUsable* m_itemToUse = nullptr;
};
