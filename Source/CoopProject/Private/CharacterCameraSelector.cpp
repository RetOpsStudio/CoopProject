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

	m_isoCamera = CreateDefaultSubobject<UIsoCharacterCameraManager>(TEXT("IsoCamera"));
	m_tpsCamera = CreateDefaultSubobject<UTPSCharacterCameraManager>(TEXT("TPSCamera"));
	m_acctualCamera = m_tpsCamera;
	// ...
}

void UCharacterCameraSelector::Setup(APlayerCharacter* playerCharacter, USpringArmComponent* cameraBoom, UCameraComponent* followCamera)
{
	m_isoCamera->Setup(playerCharacter, cameraBoom, followCamera);
	m_tpsCamera->Setup(playerCharacter, cameraBoom, followCamera);
	cameraBoom->SetupAttachment(playerCharacter->GetRootComponent());
	followCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	m_acctualCamera->SetupPlayerCamera();
}

void UCharacterCameraSelector::SwitchCamera(int camera)
{
	if (camera == 0)
	{
		m_acctualCamera = m_isoCamera;
	}
	else
	{
		m_acctualCamera = m_tpsCamera;
	}
	m_acctualCamera->SetupPlayerCamera();
}

