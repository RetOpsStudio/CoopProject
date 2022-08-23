// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "CharacterBase.h"
#include "GameFramework/Character.h"
#include "GAS/CoopAbilitySystemComponent.h"
#include "GAS/PlayerAttributeSet.h"
#include "GAS/PlayerGameplayAbilityBase.h"
#include "PlayerCharacter.generated.h"

UCLASS(config = Game)
class APlayerCharacter : public ACharacterBase, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	FVector GetCameraLocation();
protected:
	/** Called for forwards/backward input */
	void MoveForward(const float Value);

	/** Called for side to side input */
	void MoveRight(const float Value);

	/** Switch camera*/
	void SwitchCamera();


	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(const float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(const float Rate);

	void InitializeAttributes();

	void GiveAbilities();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;


	virtual void OnRep_PlayerState() override;

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	float turnRateGamepad = 2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	bool bIsMouseMovementEnabled = true;
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Ability System")
	UCoopAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UPlayerAttributeSet* Attributes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<UPlayerGameplayAbilityBase>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> m_effectGrabberTPS;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> m_effectGrabberISO;
	
private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* m_cameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* m_followCamera;

	UPROPERTY()
	class UCharacterCameraSelector* m_cameraSelector = nullptr;
};

