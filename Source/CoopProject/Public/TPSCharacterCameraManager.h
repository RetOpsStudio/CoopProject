// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterCameraManagerBase.h"
#include "TPSCharacterCameraManager.generated.h"

/**
 * 
 */
class APlayerCharacter;
class USpringArmComponent;
class UCameraComponent;
UCLASS()
class COOPPROJECT_API UTPSCharacterCameraManager : public UCharacterCameraManagerBase
{
	GENERATED_BODY()

public:
	UTPSCharacterCameraManager();
	virtual void Setup(APlayerCharacter* playerCharacter, USpringArmComponent* cameraBoom, UCameraComponent* followCamera) override;
	virtual void SetupPlayerCamera() override;

};
