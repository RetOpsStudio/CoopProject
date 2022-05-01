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
}

void UIsoCharacterCameraManager::SetupPlayerCamera()
{
	if (!m_playerCharacter)
	{
		return;
	}

	/*m_cameraBoom->SetupAttachment(m_playerCharacter->GetRootComponent());*/
	//int x = 0;
	m_cameraBoom->TargetArmLength = 800.0f; // The camera follows at this distance behind the character	
	m_cameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	m_cameraBoom->bInheritPitch = false;
	m_cameraBoom->bInheritRoll = false;
	m_cameraBoom->bInheritYaw = false;

	//m_followCamera->SetupAttachment(m_cameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	m_followCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}
