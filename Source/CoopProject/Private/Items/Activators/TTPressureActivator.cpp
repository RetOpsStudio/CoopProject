// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Activators/TTPressureActivator.h"
#include "Components/BoxComponent.h"

ATTPressureActivator::ATTPressureActivator() : Super()
{
	m_collisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	m_collisionBox->SetupAttachment(m_rootComponent);

	m_collisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m_collisionBox->SetCollisionResponseToAllChannels(ECR_Overlap);

	m_collisionBox->OnComponentBeginOverlap.AddDynamic(this, &ATTPressureActivator::OnOverlapBegin);
	m_collisionBox->OnComponentEndOverlap.AddDynamic(this, &ATTPressureActivator::OnOverlapEnd);
}

void ATTPressureActivator::Use(const FGameplayAbilityActorInfo& usingActorInfo)
{
	Super::Use(usingActorInfo);
}

void ATTPressureActivator::StopUsing(const FGameplayAbilityActorInfo& usingActorInfo)
{
	Super::StopUsing(usingActorInfo);
}

void ATTPressureActivator::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority())
	{
		return;
	}

	if (++m_currentlyOverlappingActors >= m_actorsThreshold && !m_bActivatorUsed)
	{
		m_bActivatorUsed = true;
		Use(FGameplayAbilityActorInfo());
	}
}

void ATTPressureActivator::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!HasAuthority())
	{
		return;
	}

	if (m_currentlyOverlappingActors > 0) //sanity check
	{
		--m_currentlyOverlappingActors;
	}

	if (m_currentlyOverlappingActors < m_actorsThreshold && m_bActivatorUsed)
	{
		m_bActivatorUsed = false;
		StopUsing(FGameplayAbilityActorInfo());
	}
}
