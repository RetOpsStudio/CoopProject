// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/GACrouch.h"
#include "GameFramework/Character.h"

UGACrouch::UGACrouch() : Super()
{
	AbilityInputID = EAbilityInputID::Crouch;
}

void UGACrouch::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	ACharacter* playerCharacter = Cast<ACharacter>(ActorInfo->AvatarActor);
	if (IsValid(playerCharacter))
	{
		!playerCharacter->bIsCrouched ? playerCharacter->Crouch() : playerCharacter->UnCrouch();
		
	}
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UGACrouch::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

