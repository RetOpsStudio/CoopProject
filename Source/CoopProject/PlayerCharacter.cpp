// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "CharacterCameraSelector.h"

//////////////////////////////////////////////////////////////////////////
// APlayerCharacter

APlayerCharacter::APlayerCharacter()
{
	bAlwaysRelevant = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them

	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	m_cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	m_followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	m_cameraSelector = CreateDefaultSubobject<UCharacterCameraSelector>(TEXT("CameraManager"));
	m_cameraSelector->Setup(this, m_cameraBoom, m_followCamera);

	AbilitySystemComponent = CreateDefaultSubobject<UCoopAbilitySystemComponent>(TEXT("Ability System Component"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	Attributes = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("Attributes"));

	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

//////////////////////////////////////////////////////////////////////////
// Input

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Switch Camera", IE_Pressed, this, &APlayerCharacter::SwitchCamera);
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APlayerCharacter::TurnAtRate/*&APawn::AddControllerYawInput*/);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APlayerCharacter::LookUpAtRate/*&APawn::AddControllerPitchInput*/);

	if (IsValid(InputComponent) && IsValid(AbilitySystemComponent))
	{
		const FGameplayAbilityInputBinds binds("Confirm", "Cancel", "EAbilityInputID",
			static_cast<int32>(EAbilityInputID::Confirm), static_cast<int32>(EAbilityInputID::Cancel));
		
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, binds);		
	}
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	/** Server GAS init */
	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		InitializeAttributes();
		GiveAbilities();
	}
}

void APlayerCharacter::InitializeAttributes()
{
	if (!IsValid(AbilitySystemComponent) || !IsValid(DefaultAttributeEffect))
	{
		return;
	}

	FGameplayEffectContextHandle effectContext = AbilitySystemComponent->MakeEffectContext();
	effectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle specHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, effectContext);

	if (specHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*specHandle.Data.Get());
	}
}

void APlayerCharacter::GiveAbilities()
{
	if (!HasAuthority() || !IsValid(AbilitySystemComponent))
	{
		return;
	}

	for (TSubclassOf<UPlayerGameplayAbilityBase>& ability : DefaultAbilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(ability, 1, static_cast<int32>(ability.GetDefaultObject()->AbilityInputID)));
	}
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	/** Client GAS init */
	if (!IsValid(AbilitySystemComponent))
	{
		return;
	}
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	InitializeAttributes();

	if (!IsValid(InputComponent))
	{
		return;			
	}
	
	const FGameplayAbilityInputBinds binds("Confirm", "Cancel", "EAbilityInputID",
			static_cast<int32>(EAbilityInputID::Confirm), static_cast<int32>(EAbilityInputID::Cancel));
	AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, binds);
}

UAbilitySystemComponent* APlayerCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void APlayerCharacter::TurnAtRate(const float Rate)
{
	// calculate delta for this frame from the rate information
	if(!bIsMouseMovementEnabled)
	{
		return;
	}
	AddControllerYawInput(Rate * turnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(const float Rate)
{
	if (!bIsMouseMovementEnabled)
	{
		return;
	}
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * turnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::MoveForward(const float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(const float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::SwitchCamera()
{
	if (IsValid(m_cameraSelector))
	{
		//TODO this have to be moved to Ability in order to work

		/*auto ASC = GetAbilitySystemComponent();
		FGameplayEffectContextHandle effectContext = ASC->MakeEffectContext();
		effectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle specHandle = ASC->MakeOutgoingSpec(m_effectGrabberTPS, 1, effectContext);
		if (specHandle.IsValid())
		{
			ASC->ApplyGameplayEffectSpecToSelf(*specHandle.Data.Get());
		}*/
		m_cameraSelector->SwitchCamera(ECameras::NEXT_CAMERA);
	}
}

FVector APlayerCharacter::GetCameraLocation()
{
	return m_followCamera->GetComponentLocation();
}

