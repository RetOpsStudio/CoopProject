// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCameraManagerBase.h"

UCharacterCameraManagerBase::UCharacterCameraManagerBase()
{

	PrimaryComponentTick.bCanEverTick = false;

}


void UCharacterCameraManagerBase::Setup(APlayerCharacter* playerCharacter, USpringArmComponent* cameraBoom, UCameraComponent* followCamera)
{
	m_playerCharacter = playerCharacter;
	m_cameraBoom = cameraBoom;
	m_followCamera = followCamera;
}



