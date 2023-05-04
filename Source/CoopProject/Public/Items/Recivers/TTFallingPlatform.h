// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Recivers/TTReciverBase.h"
#include "TTFallingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class COOPPROJECT_API ATTFallingPlatform : public ATTReciverBase
{
	GENERATED_BODY()
	virtual void OnItemBeginActivate_Implementation() override;
};
