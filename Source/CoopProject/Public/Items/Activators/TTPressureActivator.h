// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Activators/AItemActivatorBase.h"
#include "TTPressureActivator.generated.h"

/**
 * 
 */
UCLASS()
class COOPPROJECT_API ATTPressureActivator : public AItemActivatorBase
{
	GENERATED_BODY()

public:
	ATTPressureActivator();
	//UCharacterUsable
	virtual void Use(const struct FGameplayAbilityActorInfo& usingActorInfo) override;
	virtual void StopUsing(const struct FGameplayAbilityActorInfo& usingActorInfo) override;

protected:
	/** called when something enters the sphere component */
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** called when something leaves the sphere component */
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	int32 m_currentlyOverlappingActors = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	int32 m_actorsThreshold = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	class UBoxComponent* m_collisionBox = nullptr;

	bool m_bActivatorUsed = false;
};
