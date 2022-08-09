// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/ItemBase.h"
#include "AbilitySystemInterface.h"
#include "Components/BoxComponent.h"
#include "GAS/CoopAbilitySystemComponent.h"
#include "GameplayEffects/GEButtonPressed.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_volume = CreateDefaultSubobject<UBoxComponent>(TEXT("Volume"));
	m_volume->SetupAttachment(GetRootComponent());
	m_volume->InitBoxExtent(FVector(100.f, 100.f, 100.f));
	m_volume->SetCollisionResponseToAllChannels(ECR_Overlap);

}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	m_volume->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnItemBeginActivate);
	m_volume->OnComponentEndOverlap.AddDynamic(this, &AItemBase::OnItemCancelActivate);
	
}

///TODO move this whole logic on ability -> Actor activating item will activate ability to do so, then this component will apply effect on him
void AItemBase::OnItemBeginActivate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority())
	{
		return;
	}
	auto abilitySystemActor = Cast<IAbilitySystemInterface>(OtherActor);
	if(!abilitySystemActor)
	{
		return;
	}
		
	UE_LOG(LogTemp, Warning, TEXT("ImServer"));
	auto ASC = abilitySystemActor->GetAbilitySystemComponent();
	if (!IsValid(ASC))
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Asc Valid"));
	FGameplayEffectContextHandle effectContext = ASC->MakeEffectContext();
	effectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle specHandle = ASC->MakeOutgoingSpec(m_effectToApply, 1, effectContext);

	if (specHandle.IsValid())
	{
		ASC->ApplyGameplayEffectSpecToSelf(*specHandle.Data.Get());
	}
}

///TODO move this whole logic on ability -> Actor activating item will activate ability to do so, then this component will apply effect on him
void AItemBase::OnItemCancelActivate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!HasAuthority())
	{
		return;
	}
	auto abilitySystemActor = Cast<IAbilitySystemInterface>(OtherActor);
	if (!abilitySystemActor)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("ImServer"));
	auto ASC = abilitySystemActor->GetAbilitySystemComponent();
	if (!IsValid(ASC))
	{
		return;
	}

}


void AItemBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}



