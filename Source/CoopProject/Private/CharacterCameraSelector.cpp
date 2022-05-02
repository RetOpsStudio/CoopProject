// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCameraSelector.h"
#include "TPSCharacterCameraManager.h"
#include "IsoCharacterCameraManager.h"
#include "../PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
// Sets default values for this component's properties
UCharacterCameraSelector::UCharacterCameraSelector()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	m_cameras.Reserve(2);
	m_cameras.Add(CreateDefaultSubobject<UTPSCharacterCameraManager>(TEXT("TPSCamera")));
	m_cameras.Add(CreateDefaultSubobject<UIsoCharacterCameraManager>(TEXT("IsoCamera")));

	m_acctualCamera = ECameras::TPS_CAMERA;
	// ...
}

void UCharacterCameraSelector::Setup(APlayerCharacter* playerCharacter, USpringArmComponent* cameraBoom, UCameraComponent* followCamera)
{
	for (const auto& camera : m_cameras)
	{
		camera->Setup(playerCharacter, cameraBoom, followCamera);
	}

	cameraBoom->SetupAttachment(playerCharacter->GetRootComponent());
	followCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName); 

	m_cameras[static_cast<int>(m_acctualCamera)]->SetupPlayerCamera();
}

void UCharacterCameraSelector::SwitchCamera(ECameras cameraToSelect)
{
	if (cameraToSelect >= ECameras::NEXT_CAMERA)
	{
		m_acctualCamera = static_cast<ECameras>((static_cast<int>(m_acctualCamera) + 1) % static_cast<int>(ECameras::NEXT_CAMERA));
	}
	else
	{
		m_acctualCamera = cameraToSelect;
	}

	m_cameras[static_cast<int>(m_acctualCamera)]->SetupPlayerCamera();
}

