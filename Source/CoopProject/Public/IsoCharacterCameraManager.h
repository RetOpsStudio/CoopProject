// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterCameraManagerBase.h"
#include "IsoCharacterCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class COOPPROJECT_API UIsoCharacterCameraManager : public UCharacterCameraManagerBase
{
	GENERATED_BODY()
public:
	UIsoCharacterCameraManager();
	virtual void Setup(APlayerCharacter* playerCharacter, USpringArmComponent* cameraBoom, UCameraComponent* followCamera) override;
	virtual void SetupPlayerCamera() override;
};
