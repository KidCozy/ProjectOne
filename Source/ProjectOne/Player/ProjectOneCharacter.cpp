// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ProjectOneCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Weapons/Pistol.h"
#include "ProjectOne/Environments/GameModes/ProjectOneGameInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"


void AProjectOneCharacter::PostInitializeComponents() {
	Super::PostInitializeComponents();
	
	APAnim = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	//Controller = GetController();
	//PlayerController = World->GetFirstPlayerController();
}

// *** 리소스 로드 (초기화) ***
void AProjectOneCharacter::SetResources() {
	static ConstructorHelpers::FClassFinder<UCameraShake> CSHAKE_FIRE(TEXT("Blueprint'/Game/ScreenFX/CShake_Fire.CShake_Fire_C'"));
	
	if (CSHAKE_FIRE.Succeeded())
		CShakeList.Add(CSHAKE_FIRE.Class);
}

AProjectOneCharacter::AProjectOneCharacter()
{
	
	SetResources();

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	APAnim = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance());

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller


	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	FollowCamera->SetRelativeLocation(FVector(-50.0f, 0, 0));


	CameraBoom->TargetArmLength = 350.0f;
	CameraBoom->SocketOffset = FVector(40.0f, 100.0f, 60.0f);

	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bUseCameraLagSubstepping = true;
	CameraBoom->bDrawDebugLagMarkers = true;

	CameraBoom->CameraLagSpeed = 5.0f;
	CameraBoom->CameraLagMaxDistance = 70.0f;
	CameraBoom->CameraLagMaxTimeStep = 0.5f;
	InputVector = FVector::ZeroVector;
	Hp = 100.0f;

}

void AProjectOneCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Aim",IE_Pressed, this, &AProjectOneCharacter::Aim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AProjectOneCharacter::Aim);

	PlayerInputComponent->BindAction("Shot", IE_Pressed, this, &AProjectOneCharacter::Shot);
	PlayerInputComponent->BindAction("Shot", IE_Released, this, &AProjectOneCharacter::Shot);

	PlayerInputComponent->BindAction("ReLoad", IE_Pressed, this, &AProjectOneCharacter::ReLoad);


	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AProjectOneCharacter::DoCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AProjectOneCharacter::DoCrouch);

	PlayerInputComponent->BindAction("MoveInput", IE_Released, this, &AProjectOneCharacter::MoveReleased);

	PlayerInputComponent->BindAxis("MoveForward", this, &AProjectOneCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AProjectOneCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AProjectOneCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AProjectOneCharacter::LookUpAtRate);
	

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AProjectOneCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AProjectOneCharacter::TouchStopped);
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AProjectOneCharacter::OnResetVR);
	
	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &AProjectOneCharacter::Roll);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AProjectOneCharacter::JumpInput);
}


void AProjectOneCharacter::Tick(float delta) {
	Super::Tick(delta);
	if (APAnim->isAim) {
		GetFollowCamera()->SetFieldOfView(FMath::Lerp(GetFollowCamera()->FieldOfView, 40.0f, 0.1f));
	}
	else {
		GetFollowCamera()->SetFieldOfView(FMath::Lerp(GetFollowCamera()->FieldOfView, 100.0f, 0.1f));
	}
	Shooting(delta);
}

void AProjectOneCharacter::BeginPlay()
{
	Super::BeginPlay();
	FVector SpawnPos(100.0f, 0.0f, 50.0f);
	Pistol = GetWorld()->SpawnActor<AWeapon>(SpawnPos, FRotator::ZeroRotator);
	FAttachmentTransformRules test(EAttachmentRule::KeepRelative, false);
	Pistol->SetOwner(this);
	Pistol->AttachToActor(GetWorld()->GetFirstPlayerController()->GetPawn(), test);
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
	FTimerHandle time_;

	if (!APAnim->isAim) {
		APAnim->isAim = true;
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		CameraBoom->bEnableCameraLag = false;
	}
	else {
		APAnim->isAim = false;
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		CameraBoom->bEnableCameraLag = true;
	}

	//GetWorld()->GetTimerManager().SetTimer(time_, this, &AProjectOneCharacter::AimLerp, 50.0f, true, 1.0f);
}
void AProjectOneCharacter::AimLerp()
{
		if(APAnim->isAim)
			GetFollowCamera()->SetFieldOfView(FMath::Lerp(GetFollowCamera()->FieldOfView, 60.0f, 0.1f));
		else
			GetFollowCamera()->SetFieldOfView(FMath::Lerp(GetFollowCamera()->FieldOfView, 100.0f, 0.1f));

}

void AProjectOneCharacter::Shot()
{
	GetCapsuleComponent()->SetRelativeRotation(FRotator(0.0f, FollowCamera->GetComponentRotation().Yaw, 0.0f));


	if (!isShooting) {
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->MaxWalkSpeed = 450.0f;
		intervalTime = Pistol->IntervalTime;
		isShooting = true;
	}
	else {
		if (!APAnim->isAim) {
			GetCharacterMovement()->bUseControllerDesiredRotation = false;
			GetCharacterMovement()->bOrientRotationToMovement = true;
			GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		}
		isShooting = false;
	}

}

void AProjectOneCharacter::Roll()
{
	if (!GetCharacterMovement()->IsFalling() 
		&&	!APAnim->isRoll
		&& !APAnim->Montage_IsPlaying(APAnim->RollMontage)
		&& !APAnim->isAim
		&& !APAnim->isInAir)
	{
		APAnim->isRoll = true;
		FRotator DirectionVec = InputVector.GetSafeNormal().Rotation() + FollowCamera->GetComponentRotation().GetNormalized();
		DirectionVec.Pitch = 0.0f;
		DirectionVec.Roll = 0.0f;
		GetCapsuleComponent()->SetRelativeRotation(DirectionVec);
		APAnim->Montage_Play(APAnim->RollMontage);
		InputVector = FVector::ZeroVector;
	}
}

void AProjectOneCharacter::MoveReleased()
{
		InputVector = FVector::ZeroVector;
}

void AProjectOneCharacter::JumpInput()
{
	if (!APAnim->isInAir && !APAnim->isRoll) {
		Jump();
		APAnim->isInAir = true;
	}
}

void AProjectOneCharacter::Shooting(float tick)
{
	if (isShooting) {
		if (intervalTime >= Pistol->IntervalTime) {
			FTimerHandle time_;//bulletCheck
			if (Pistol->NowBulletNum <= 0)
				return;
			Pistol->Shot(Pistol->GetActorLocation(), GetCharacterToAimeVec());

			//shake
			auto GameInstance = Cast<UProjectOneGameInstance>(GetGameInstance());
			GameInstance->HitShake(GameInstance->CShakePistol, 1.0f);

			//Recoil
			Rebound();
		}
		intervalTime -= tick;
		if (intervalTime <= 0.0f) {
			intervalTime = Pistol->IntervalTime;
		}
	}
}



void AProjectOneCharacter::ReLoad()
{
	Pistol->ReLoad();
}

void AProjectOneCharacter::Hit(float Damage, AActor * Causer)
{
	if (Hp - Damage <= 0) {
		Hp = 0;
		auto CauserPlayer = Cast<AProjectOneCharacter>(Causer);
		CauserPlayer->Evolution();
		Dead();
	}
	else
		Hp = Hp - Damage;
}

void AProjectOneCharacter::DoCrouch() {
	if (APAnim->isCrouch) {
		UnCrouch();
		APAnim->isCrouch = false;
	}
	else {
		Crouch();
		APAnim->isCrouch = true;
	}
}

void AProjectOneCharacter::PlayCShake(int Index) {
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(CShakeList[Index]);

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
	if ((Controller != NULL) && (Value != 0.0f) && !APAnim->isRoll)
	{
		InputVector.X = Value;

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
	if ( (Controller != NULL) && (Value != 0.0f) &&!APAnim->isRoll)
	{
		InputVector.Y = Value;

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

FVector AProjectOneCharacter::GetCharacterToAimeVec()
{

	FHitResult OutHit;
	FVector CameraForwardVector = FollowCamera->GetComponentRotation().Vector();
	FVector AimeStart = (CameraForwardVector*200.0f) + FollowCamera->GetComponentLocation();
	FVector AimEnd = (CameraForwardVector*3000.0f) + AimeStart;
	FCollisionQueryParams CameraCollisionParams;

	FVector tmpVec = AimEnd;

	if (GetWorld()->LineTraceSingleByChannel(OutHit, AimeStart, AimEnd, ECC_Visibility, CameraCollisionParams)) {
		tmpVec = OutHit.ImpactPoint;
	}
	FVector reVal = tmpVec - Pistol->GetActorLocation();

	return reVal.GetSafeNormal();
}

void AProjectOneCharacter::Rebound()
{
	float PitchVal = FMath::RandRange(Pistol->VerticalRecoil * 0.7f, Pistol->VerticalRecoil);
	float YawVal = FMath::RandRange(-Pistol->HorizonRecoil * 0.5f, Pistol->HorizonRecoil*0.5f);
	AddControllerPitchInput(-PitchVal);
	AddControllerYawInput(YawVal);
}

void AProjectOneCharacter::Dead()
{
	ABLOG_S(Warning);
}

void AProjectOneCharacter::Evolution()
{
	SetActorScale3D(FVector(1.1f, 1.1f, 1.1f));
}