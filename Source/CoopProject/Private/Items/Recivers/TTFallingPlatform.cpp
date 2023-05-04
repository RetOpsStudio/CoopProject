// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Recivers/TTFallingPlatform.h"

void ATTFallingPlatform::OnItemBeginActivate_Implementation()
{
	m_staticMesh->SetSimulatePhysics(true);
	m_staticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
}
