// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ProjectOneCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AProjectOneCharacter

void AProjectOneCharacter::PostInitializeComponents() {
	Super::PostInitializeComponents();
	APAnim = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance());
}

AProjectOneCharacter::AProjectOneCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	APAnim = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance());

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	FollowCamera->SetRelativeLocation(FVector(-50.0f, 0, 0));

	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->SocketOffset = FVector(50.0f, 100.0f, 70.0f);

	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bUseCameraLagSubstepping = true;
	CameraBoom->bDrawDebugLagMarkers = true;

	CameraBoom->CameraLagSpeed = 5.0f;
	CameraBoom->CameraLagMaxDistance = 70.0f;
	CameraBoom->CameraLagMaxTimeStep = 0.5f;
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProjectOneCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Aim",IE_Pressed, this, &AProjectOneCharacter::Aim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AProjectOneCharacter::Aim);


	PlayerInputComponent->BindAxis("MoveForward", this, &AProjectOneCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AProjectOneCharacter::MoveRight);
	

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AProjectOneCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AProjectOneCharacter::LookUpAtRate);


	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AProjectOneCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AProjectOneCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AProjectOneCharacter::OnResetVR);
}


void AProjectOneCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AProjectOneCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AProjectOneCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AProjectOneCharacter::Aim()
{
	if (!APAnim->isAim) {
		APAnim->isAim = true;
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	}
	else {
		APAnim->isAim = false;
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;

	}
}

void AProjectOneCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AProjectOneCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AProjectOneCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		
		APAnim->Forward = Value * 100.0f;
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AProjectOneCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		APAnim->Right = Value * 100.0f;

		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
