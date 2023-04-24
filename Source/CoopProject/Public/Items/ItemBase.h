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

	UFUNCTION()
	virtual void  StopUsingItem(const FGameplayAbilityActorInfo& usingActorInfo);

protected:
	//AActor //TODO add to every class
	virtual void BeginPlay() override;
	//~AActor

	UFUNCTION()
	virtual void OnItemBeginActivate();

	UFUNCTION()
	virtual void OnItemCancelActivate();

	UFUNCTION()
	virtual void OnItemEndActivate();

	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "OnItemBeginActivate"))
	void OnItemBeginActivateBP(); //delete BP from name
	virtual void OnItemBeginActivateBP_Implementation();

	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "OnItemCancelActivate"))
	void OnItemCancelActivateBP();
	virtual void OnItemCancelActivateBP_Implementation();

	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "OnItemEndActivate"))
	void OnItemEndActivateBP();
	virtual void OnItemEndActivateBP_Implementation();

	virtual void PostInitializeComponents() override;
};
