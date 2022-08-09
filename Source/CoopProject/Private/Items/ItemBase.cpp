// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/ItemBase.h"
#include "AbilitySystemInterface.h"
#include "Components/BoxComponent.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_volume = CreateDefaultSubobject<UBoxComponent>(TEXT("Volume"));
	m_volume->SetupAttachment(GetRootComponent());
	m_volume->InitBoxExtent(FVector(1000.f, 1000.f, 1000.f));
	m_volume->SetCollisionResponseToAllChannels(ECR_Overlap);

}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	m_volume->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnItemBeginActivate);
	m_volume->OnComponentEndOverlap.AddDynamic(this, &AItemBase::OnItemCancelActivate);
	
}
void AItemBase::OnItemBeginActivate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<IAbilitySystemInterface>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Cast successfull entering"));
	}
	UE_LOG(LogTemp, Warning, TEXT("entering"));

}
void AItemBase::OnItemCancelActivate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<IAbilitySystemInterface>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Cast successfull Leaving"));
	}
	UE_LOG(LogTemp, Warning, TEXT("Leaving"));
}


void AItemBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

//// Called every frame
//void AItemBase::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

