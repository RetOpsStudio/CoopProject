// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/ItemBase.h"


// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();	
}



void AItemBase::UseItem(const FGameplayAbilityActorInfo& usingActorInfo)
{
	//if (!HasAuthority()) //figure out if this is neccesary here
	//{
	//	return;
	//}
	OnItemBeginActivate();
}

void AItemBase::StopUsingItem(const FGameplayAbilityActorInfo& usingActorInfo)
{
	//if (!HasAuthority()) //figure out if this is neccesary here
	//{
	//	return;
	//}
	OnItemEndActivate();
}

void AItemBase::OnItemBeginActivate()
{
	OnItemBeginActivateBP();
}

void AItemBase::OnItemCancelActivate()
{
	OnItemCancelActivateBP();
}

void AItemBase::OnItemEndActivate()
{
	OnItemEndActivateBP();
}

void AItemBase::OnItemBeginActivateBP_Implementation()
{
	//logic here
}

void AItemBase::OnItemEndActivateBP_Implementation()
{
	//logic here
}
void AItemBase::OnItemCancelActivateBP_Implementation()
{
	//logic here
}
void AItemBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}



