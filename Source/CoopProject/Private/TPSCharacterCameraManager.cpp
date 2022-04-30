// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSCharacterCameraManager.h"


#include "../PlayerCharacter.h"
// Copyright Epic Games, Inc. All Rights Reserved.

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

UTPSCharacterCameraManager::UTPSCharacterCameraManager()
{

}

void UTPSCharacterCameraManager::Setup(APlayerCharacter* playerCharacter, USpringArmComponent* cameraBoom, UCameraComponent* followCamera)
{
	m_playerCharacter = playerCharacter;
	m_cameraBoom = cameraBoom;
	m_followCamera = followCamera;

	SetupPlayerCamera();
}

void UTPSCharacterCameraManager::SetupPlayerCamera()
{
	if (!m_playerCharacter)
	{
		return;
	}

	m_cameraBoom->SetupAttachment(m_playerCharacter->GetRootComponent());
	m_cameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	m_cameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	m_followCamera->SetupAttachment(m_cameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	m_followCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}
