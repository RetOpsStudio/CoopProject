// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterCameraSelector.generated.h"

class APlayerCharacter;
class USpringArmComponent;
class UCameraComponent;
UENUM()
enum class ECameras
{
	TPS_CAMERA          UMETA(DisplayName = "TPS Camera"),
	ISOMETRIC_CAMERA    UMETA(DisplayName = "Isometric Camera"),
	NEXT_CAMERA         UMETA(DisplayName = "Next Camera"),
};
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COOPPROJECT_API UCharacterCameraSelector : public UActorComponent
{
	GENERATED_BODY()

public:	



	// Sets default values for this component's properties
	UCharacterCameraSelector();

	void Setup(APlayerCharacter* playerCharacter, USpringArmComponent* cameraBoom, UCameraComponent* followCamera);
	void SwitchCamera(ECameras cameraToSelect);
protected:

public:	

	UPROPERTY()
	ECameras m_acctualCamera = ECameras::TPS_CAMERA;
	UPROPERTY()
	TArray<class UCharacterCameraManagerBase*> m_cameras;
		
};
