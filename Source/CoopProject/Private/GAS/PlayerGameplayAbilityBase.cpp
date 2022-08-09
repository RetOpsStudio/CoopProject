// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/PlayerGameplayAbilityBase.h"
#include "GAS/CoopAbilitySystemComponent.h"
UPlayerGameplayAbilityBase::UPlayerGameplayAbilityBase()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UPlayerGameplayAbilityBase::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (bActivateAbilityOnSet)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}

}