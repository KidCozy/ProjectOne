// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ProjectOneCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Weapons/Pistol.h"
#include "ProjectOne/Environments/GameModes/ProjectOneGameInstance.h"
#include "PlayerStatComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperSpriteComponent.h"
#include "AI/AICharacter.h"


void AProjectOneCharacter::PostInitializeComponents() {
	Super::PostInitializeComponents();
	SetComponents();
}

// *** 리소스 로드 (초기화) ***
void AProjectOneCharacter::SetResources() {
	//static ConstructorHelpers::FClassFinder<UCameraShake> CSHAKE_FIRE(TEXT("Blueprint'/Game/ScreenFX/CShake_Fire.CShake_Fire_C'"));
	//if (CSHAKE_FIRE.Succeeded())
	//	CShakeList.Add(CSHAKE_FIRE.Class);

	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> ChildChracter(TEXT("SkeletalMesh'/Game/Animations/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	//if (ChildChracter.Succeeded())
	//	GetMesh()->SetSkeletalMesh(ChildChracter.Object);

	//GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -32.0f), FRotator(0.0f, -90.0f, 0.0f));

	//static ConstructorHelpers::FClassFinder<UAnimInstance> TEMP_ANIM(TEXT("AnimBlueprint'/Game/Animations/AnimationBlueprint/PlayerCharacter_AnimBP.PlayerCharacter_AnimBP_C'"));
	//if (TEMP_ANIM.Succeeded())
	//	GetMesh()->SetAnimInstanceClass(TEMP_ANIM.Class);


}

void AProjectOneCharacter::SetComponents()
{
	APAnim = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance());
}

void AProjectOneCharacter::SetInitWeapone()
{
	CharacterStat->SetWeaponeID(1);
	FPOWeaponeData* stat = CharacterStat->GetWeaphoneStatData();
	Weapone->InitWeapone(
		stat->Magazine, stat->Vertical_recoil*0.1f, stat->Horizon_recoil*0.1f,
		stat->Spread*3.0f, stat->Reload_speed, 30.0f, stat->Range);
}


AProjectOneCharacter::AProjectOneCharacter()
{
	SetResources();
	GetCapsuleComponent()->InitCapsuleSize(24.0f, 32.0f);

	APAnim = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	CharacterStat = CreateDefaultSubobject<UPlayerStatComponent>(TEXT("CharcterStat"));
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

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
	CameraBoom->SocketOffset = FVector(40.0f, 50.0f, 60.0f);

	InputVector = FVector::ZeroVector;
	Hp = 100.0f;

	IsAlive = true;
	DeadTime = 3;
}

void AProjectOneCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Shot", IE_Pressed, this, &AProjectOneCharacter::Shot);
	PlayerInputComponent->BindAction("Shot", IE_Released, this, &AProjectOneCharacter::Shot);

	PlayerInputComponent->BindAction("ReLoad", IE_Pressed, this, &AProjectOneCharacter::ReLoad);


	PlayerInputComponent->BindAction("Forward", IE_DoubleClick, this, &AProjectOneCharacter::ForwardDash);
	PlayerInputComponent->BindAction("Back", IE_DoubleClick, this, &AProjectOneCharacter::BackDash);
	PlayerInputComponent->BindAction("Left", IE_DoubleClick, this, &AProjectOneCharacter::LeftDash);
	PlayerInputComponent->BindAction("Right", IE_DoubleClick, this, &AProjectOneCharacter::RightDash);
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
	Shooting(delta);
}

void AProjectOneCharacter::BeginPlay()
{
	Super::BeginPlay();
	FVector SpawnPos(8.0f, 0.0f, 2.0f);
	Weapone = GetWorld()->SpawnActor<AWeapon>(SpawnPos, FRotator::ZeroRotator);
	FAttachmentTransformRules AttachmerRules(EAttachmentRule::KeepRelative, false);
	Weapone->SetOwner(this);
	Weapone->AttachToActor(this, AttachmerRules);

	
	SetInitWeapone();
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

void AProjectOneCharacter::Shot()
{
	if (!isShooting) {
		if (!APAnim->Montage_IsPlaying(APAnim->RollMontage)) {
			GetCharacterMovement()->MaxWalkSpeed = 450.0f;
		}
		intervalTime = Weapone->IntervalTime;
		isShooting = true;
	}
	else {
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		isShooting = false;
	}

}

void AProjectOneCharacter::Roll()
{
	if (CanRoll())
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
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
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
		if (intervalTime >= Weapone->IntervalTime) {
			FTimerHandle time_;//bulletCheck
			if (Weapone->CurBulletCount <= 0)
				return;
			
			//Spread Bullet
			float RandPitch = FMath::RandRange(-(Weapone->Spread*0.5f), Weapone->Spread*0.5f);
			float RandYaw = FMath::RandRange(-(Weapone->Spread*0.5f), Weapone->Spread*0.5f);
			
			FRotator SpreadRotation = FRotator(
				GetCharacterToAimeVec().Rotation().Pitch+RandPitch, 
				GetCharacterToAimeVec().Rotation().Yaw + RandYaw, 0.0f);

			FVector SpreadVec = SpreadRotation.Vector().GetSafeNormal();
			Weapone->Shot(Weapone->GetActorLocation(), SpreadVec, ScratchNormal);

			//shake
			auto GameInstance = Cast<UProjectOneGameInstance>(GetGameInstance());
			GameInstance->HitShake(GameInstance->CShakePistol, 1.0f);

			//Recoil
			float PitchVal = FMath::RandRange(Weapone->VerticalRecoil * 0.7f, Weapone->VerticalRecoil);
			float YawVal = FMath::RandRange(-Weapone->HorizonRecoil * 0.5f, Weapone->HorizonRecoil*0.5f);
			AddControllerPitchInput(-PitchVal);
			AddControllerYawInput(YawVal);
		}
		intervalTime -= tick;
		if (intervalTime <= 0.0f) {
			intervalTime = Weapone->IntervalTime;
		}
	}
}

void AProjectOneCharacter::ReLoad()
{
	Weapone->ReLoad();
}

void AProjectOneCharacter::Hit(float Damage, AActor * Causer)
{
	if (Hp - Damage <= 0) {
		Hp = 0;
		auto CauserPlayer = Cast<AProjectOneCharacter>(Causer);
		CauserPlayer->Evolution();

		IsAlive = false;
		GetWorld()->GetTimerManager().SetTimer(DeadTimer, this, &AProjectOneCharacter::Dead, 1.0f, true);

		auto AI = Cast<AAICharacter>(Causer);
		if (AI)
			AI->TargetPlayer = NULL;
	}
	else
		Hp = Hp - Damage;
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
	if (Value) {
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}
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
	if (Value) {
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}
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
	FVector AimeStart = (CameraForwardVector*400.0f) + FollowCamera->GetComponentLocation();
	FVector AimEnd = (CameraForwardVector*3000.0f) + AimeStart;
	FCollisionQueryParams CameraCollisionParams;

	FVector tmpVec = AimEnd;

	if (GetWorld()->LineTraceSingleByChannel(OutHit, AimeStart, AimEnd, ECC_Visibility, CameraCollisionParams)) {
		tmpVec = OutHit.ImpactPoint;
		ScratchNormal = OutHit.Normal;
	}
	else
		ScratchNormal = FVector::ZeroVector;
	
	FVector reVal = tmpVec - Weapone->GetActorLocation();

	return reVal.GetSafeNormal();
}

void AProjectOneCharacter::Dead()
{
	DeadTime--;

	if (DeadTime < 1)
	{
		GetWorldTimerManager().ClearTimer(DeadTimer);
		Destroy(this);
	}
	ABLOG_S(Warning);
}

void AProjectOneCharacter::Evolution()
{
	SetActorScale3D(FVector(1.1f, 1.1f, 1.1f));
}

bool AProjectOneCharacter::CanRoll()
{
	return (!APAnim->isRoll && !APAnim->Montage_IsPlaying(APAnim->RollMontage) && !APAnim->isInAir) ? true : false;
}

void AProjectOneCharacter::ForwardDash()
{
	if (CanRoll())
	{
		GetCapsuleComponent()->SetRelativeRotation(
			FRotator(0.0f, FollowCamera->GetComponentRotation().GetNormalized().Yaw, 0.0f)
		);
		APAnim->Montage_Play(APAnim->RollMontage);
	}
}

void AProjectOneCharacter::BackDash()
{
	if (CanRoll())
	{
		GetCapsuleComponent()->SetRelativeRotation(
			FRotator(0.0f, FollowCamera->GetComponentRotation().GetNormalized().Yaw - 180.0f, 0.0f)
		);
		APAnim->Montage_Play(APAnim->RollMontage);
	}
}

void AProjectOneCharacter::LeftDash()
{
	if (CanRoll())
	{
		GetCapsuleComponent()->SetRelativeRotation(
			FRotator(0.0f, FollowCamera->GetComponentRotation().GetNormalized().Yaw - 90.0f,0.0f)
		);
		APAnim->Montage_Play(APAnim->RollMontage);
	}
}

void AProjectOneCharacter::RightDash()
{
	if (CanRoll())
	{
		GetCapsuleComponent()->SetRelativeRotation(
			FRotator(0.0f, FollowCamera->GetComponentRotation().GetNormalized().Yaw + 90.0f, 0.0f)
		);
		APAnim->Montage_Play(APAnim->RollMontage);
	}
}