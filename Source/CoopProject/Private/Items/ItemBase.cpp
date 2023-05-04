// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/ItemBase.h"
#include "Components/SceneComponent.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	m_rootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(m_rootComponent);

	m_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_staticMesh->SetupAttachment(m_rootComponent);
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();	
}

void AItemBase::UseItem(const FGameplayAbilityActorInfo& usingActorInfo)
{
	OnItemBeginActivate();
}

void AItemBase::StopUsingItem(const FGameplayAbilityActorInfo& usingActorInfo)
{

	OnItemEndActivate();
}

void AItemBase::OnItemBeginActivate_Implementation()
{
	OnItemBeginActivateBP();
}

void AItemBase::OnItemCancelActivate_Implementation()
{
	OnItemCancelActivateBP();
}

void AItemBase::OnItemEndActivate_Implementation()
{
	OnItemEndActivateBP();
}

void AItemBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}



