// Fill out your copyright notice in the Description page of Project Settings.


#include "IsoCharacterCameraManager.h"
#include "../PlayerCharacter.h"
// Copyright Epic Games, Inc. All Rights Reserved.

#include "Camera/CameraComponent.h"
#include "CharacterCameraManagerBase.h"
#include "GameFramework/SpringArmComponent.h"

UIsoCharacterCameraManager::UIsoCharacterCameraManager()
{

}




void UIsoCharacterCameraManager::Setup(APlayerCharacter* playerCharacter, USpringArmComponent* cameraBoom, UCameraComponent* followCamera)
{
	Super::Setup(playerCharacter, cameraBoom, followCamera);
	m_cameraBoomLength = 700.f;
}

void UIsoCharacterCameraManager::SetupPlayerCamera()
{
	if (!m_playerCharacter)
	{
		return;
	}

	m_playerCharacter->bIsMouseMovementEnabled = false;

	m_cameraBoom->TargetArmLength = m_cameraBoomLength; // The camera follows at this distance behind the character	
	m_cameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	m_cameraBoom->bInheritPitch = false;
	m_cameraBoom->bInheritRoll = false;
	m_cameraBoom->bInheritYaw = false;


	auto playerRotation = m_playerCharacter->GetControlRotation();	
	playerRotation.Pitch = m_cameraBoomAngle;

	m_cameraBoom->SetRelativeRotation(playerRotation);

	m_followCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}
