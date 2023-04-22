// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GAS/PlayerGameplayAbilityBase.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "ItemBase.generated.h"

UCLASS()
class COOPPROJECT_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();
	virtual ~AItemBase() = default;
	UFUNCTION()
	virtual void  UseItem(const FGameplayAbilityActorInfo& usingActorInfo);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnItemBeginActivate();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnItemBeginActivate"))
	void OnItemBeginActivateBP();

	UFUNCTION()
	virtual void OnItemCancelActivate();

	virtual void PostInitializeComponents() override;


};
