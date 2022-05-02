// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSCharacterCameraManager.h"


#include "../PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

UTPSCharacterCameraManager::UTPSCharacterCameraManager()
{

}




void UTPSCharacterCameraManager::Setup(APlayerCharacter* playerCharacter, USpringArmComponent* cameraBoom, UCameraComponent* followCamera)
{
	Super::Setup(playerCharacter, cameraBoom, followCamera);
}

void UTPSCharacterCameraManager::SetupPlayerCamera()
{
	if (!m_playerCharacter)
	{
		return;
	}
	m_playerCharacter->bIsMouseMovementEnabled = true;

	m_cameraBoom->TargetArmLength = m_cameraBoomLength; // The camera follows at this distance behind the character	
	m_cameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	m_cameraBoom->bInheritPitch = true;
	m_cameraBoom->bInheritRoll = true;
	m_cameraBoom->bInheritYaw = true;

	m_followCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}
