// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCameraManagerBase.h"

// Sets default values for this component's properties
UCharacterCameraManagerBase::UCharacterCameraManagerBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UCharacterCameraManagerBase::Setup(APlayerCharacter* playerCharacter, USpringArmComponent* cameraBoom, UCameraComponent* followCamera)
{
	m_playerCharacter = playerCharacter;
	m_cameraBoom = cameraBoom;
	m_followCamera = followCamera;
}



