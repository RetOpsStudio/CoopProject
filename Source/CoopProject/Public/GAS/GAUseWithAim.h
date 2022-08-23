// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GAUse.h"
#include "GAUseWithAim.generated.h"

/**
 * 
 */
UCLASS()
class COOPPROJECT_API UGAUseWithAim : public UGAUse
{
	GENERATED_BODY()
protected:
	/*Override this in child classes to implement other types of trace*/
	virtual void TraceForHits(const FGameplayAbilityActorInfo* ActorInfo, TArray<FHitResult>& outHits) override;
	
};
