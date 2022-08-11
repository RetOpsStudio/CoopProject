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
	m_volume->InitBoxExtent(FVector(50.f, 50.f, 50.f));
	m_volume->SetCollisionResponseToAllChannels(ECR_Overlap);

}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();	
}


///TODO move this whole logic on ability -> Actor activating item will activate ability to do so, then this component will apply effect on him
void AItemBase::UseItem(const FGameplayAbilityActorInfo& usingActorInfo)
{
	if (!HasAuthority())
	{
		return;
	}

	PutGameplayEffectOnUsingActor(usingActorInfo);


	OnItemBeginActivate();
}
void AItemBase::PutGameplayEffectOnUsingActor(const FGameplayAbilityActorInfo& usingActorInfo)
{
	//TODO find if that shouldnt be refactored
	if (!IsValid(m_effectToApply))
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("ImServer"));
	auto ASC = usingActorInfo.AbilitySystemComponent;

	FGameplayEffectContextHandle effectContext = ASC->MakeEffectContext();
	effectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle specHandle = ASC->MakeOutgoingSpec(m_effectToApply, 1, effectContext);

	if (specHandle.IsValid())
	{
		ASC->ApplyGameplayEffectSpecToSelf(*specHandle.Data.Get());
	}
}
void AItemBase::OnItemBeginActivate()
{
	//TODO Rmove this
	this->GetRootComponent()->AddLocalRotation(FQuat(20, 2, 2, 2));
}

void AItemBase::OnItemCancelActivate()
{
	
}


void AItemBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}



