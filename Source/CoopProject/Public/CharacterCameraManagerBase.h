// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterCameraManagerBase.generated.h"

class APlayerCharacter;
class USpringArmComponent;
class UCameraComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COOPPROJECT_API UCharacterCameraManagerBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterCameraManagerBase();

	virtual void Setup(APlayerCharacter* playerCharacter, USpringArmComponent* cameraBoom, UCameraComponent* followCamera);
	virtual void SetupPlayerCamera() { return; }

protected:
	UPROPERTY()
	USpringArmComponent* m_cameraBoom = nullptr;
	UPROPERTY()
	UCameraComponent* m_followCamera = nullptr;
	UPROPERTY()
	APlayerCharacter* m_playerCharacter = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float m_cameraBoomLength = 400.f;

		
};
