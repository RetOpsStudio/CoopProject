// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterCameraSelector.generated.h"

class APlayerCharacter;
class USpringArmComponent;
class UCameraComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COOPPROJECT_API UCharacterCameraSelector : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterCameraSelector();

	void Setup(APlayerCharacter* playerCharacter, USpringArmComponent* cameraBoom, UCameraComponent* followCamera);
	void SwitchCamera(int camera);
protected:

public:	
	UPROPERTY()
		class UIsoCharacterCameraManager* m_isoCamera = nullptr;
	UPROPERTY()
		class UTPSCharacterCameraManager* m_tpsCamera = nullptr;
	UPROPERTY()
		class UCharacterCameraManagerBase* m_acctualCamera = nullptr;
		
};
