// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ProjectOneCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "ProjectOne/Environments/GameModes/ProjectOneGameInstance.h"
#include "POComponents/PlayerStatComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/Widget.h"
#include "Components/InputComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperSpriteComponent.h"
#include "AI/AICharacter.h"
#include "LauncherCharacter.h"
#include "Weapons/SuperGun.h"
#include "Weapons/Pistol.h"
#include "POComponents/InventoryComponent.h"
#include "Environments/GameModes/ProjectOneGameState.h" 

void AProjectOneCharacter::PostInitializeComponents() {
	Super::PostInitializeComponents();
	SetComponents();
}

// *** 리소스 로드 (초기화) ***
void AProjectOneCharacter::SetResources() {
}

void AProjectOneCharacter::SetComponents()
{
	APAnim = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance());
}



AProjectOneCharacter::AProjectOneCharacter()
{
	SetResources();
	GetCapsuleComponent()->InitCapsuleSize(30.0f, 42.0f);

	APAnim = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance());
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
	CameraBoom->ProbeSize = 20.0f;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	FollowCamera->SetRelativeLocation(FVector(-50.0f, 0, 0));

	CameraBoom->TargetArmLength = 350.0f;

	CameraBoom->SocketOffset = FVector(240.0f, 40.0f, 50.0f);

	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	Inventory->SetupAttachment(RootComponent);
	Inventory->SetRelativeLocation(FVector(0.0f));

	InputVector = FVector::ZeroVector;

	CharacterStat = CreateDefaultSubobject<UPlayerStatComponent>(TEXT("CharcterStat"));
	CharacterStat->CurHP = 200.0f;
	CharacterStat->SetCharacterID(1);


	IsAlive = true;
	DeadTime = 3;
	CurLevel = 0;
	SheildEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SHEILDEFFECT"));
	SheildEffect->SetupAttachment(RootComponent);

	HealEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HEALEFFECT"));
	HealEffect->SetupAttachment(RootComponent);

	Gun = CreateDefaultSubobject<USuperGun>(TEXT("Gun"));

	isPause = false;
}

void AProjectOneCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Shot", IE_Pressed, this, &AProjectOneCharacter::Shot);
	PlayerInputComponent->BindAction("Shot", IE_Released, this, &AProjectOneCharacter::Shot);

	PlayerInputComponent->BindAction("ReLoad", IE_Pressed, this, &AProjectOneCharacter::ReloadAnimPlay);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AProjectOneCharacter::Aim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AProjectOneCharacter::Aim);


	PlayerInputComponent->BindAction("Item1", IE_Pressed, this, &AProjectOneCharacter::UseItem1);
	PlayerInputComponent->BindAction("Item2", IE_Pressed, this, &AProjectOneCharacter::UseItem2);
	PlayerInputComponent->BindAction("Item3", IE_Pressed, this, &AProjectOneCharacter::UseItem3);
	PlayerInputComponent->BindAction("Item4", IE_Pressed, this, &AProjectOneCharacter::UseItem4);
	PlayerInputComponent->BindAction("Item5", IE_Pressed, this, &AProjectOneCharacter::UseItem5);

	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &AProjectOneCharacter::Roll);
	PlayerInputComponent->BindAction("Evolution", IE_Pressed, this, &AProjectOneCharacter::Evolution);


	PlayerInputComponent->BindAction("MoveInput", IE_Released, this, &AProjectOneCharacter::MoveReleased);

	PlayerInputComponent->BindAxis("MoveForward", this, &AProjectOneCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AProjectOneCharacter::MoveRight);


	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AProjectOneCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AProjectOneCharacter::LookUpAtRate);

}


void AProjectOneCharacter::Tick(float delta) {
	Super::Tick(delta);
	if (isAim) {
		GetFollowCamera()->SetFieldOfView(FMath::Lerp(GetFollowCamera()->FieldOfView, 20.0f, 0.1f));
		GetCameraBoom()->TargetArmLength = 240;
		//GetCameraBoom()->TargetOffset = FVector(120, GetCameraBoom()->TargetOffset.Y, GetCameraBoom()->TargetOffset.Z);
		GetMesh()->SetVisibility(false);
	}
	else {
		GetFollowCamera()->SetFieldOfView(FMath::Lerp(GetFollowCamera()->FieldOfView, 100.0f, 0.1f));
		GetCameraBoom()->TargetArmLength = 350;
		GetMesh()->SetVisibility(true);

		//   GetCameraBoom()->TargetOffset = FVector(0, GetCameraBoom()->TargetOffset.Y, GetCameraBoom()->TargetOffset.Z);
	}

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

	AProjectOneGameState* GameState = Cast<AProjectOneGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (IsValid(GameState))
		GameState->AlivePlayers.Add(this);

}


void AProjectOneCharacter::PossessedBy(AController * ct)
{
	Super::PossessedBy(ct);

}

void AProjectOneCharacter::Shot()
{
	if (!isShooting) {
		isShooting = true;
	}
	else {
		isShooting = false;
	}
	APAnim->isShooting = isShooting;
}

void AProjectOneCharacter::Roll()
{
	if (!APAnim->isRoll)
	{
		switch (rollDir)
		{
		case RollDir::RIGHT:
			APAnim->Montage_Play(APAnim->R_RollMontage);
			APAnim->isRoll = true;
			break;
		case RollDir::LEFT:
			APAnim->Montage_Play(APAnim->L_RollMontage);
			APAnim->isRoll = true;
			break;
		}
		InputVector = FVector::ZeroVector;
	}
}

void AProjectOneCharacter::Aim()
{
	if (!isAim) {
		isAim = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}
	else {
		isAim = false;

		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}
}

void AProjectOneCharacter::ReloadAnimPlay()
{
	if (APAnim->isRoll ||
		APAnim->Montage_IsPlaying(APAnim->ReloadMontage))
		return;
	APAnim->Montage_Play(APAnim->ReloadMontage);
}

void AProjectOneCharacter::MoveReleased()
{
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	rollDir = RollDir::RELEASE;
}


void AProjectOneCharacter::Shooting(float tick)
{
	//자동 재장전
	if (Gun->GetCurBullet() <= 0) {
		ReloadAnimPlay();
	}

	if (!isShooting || APAnim->Montage_IsPlaying(APAnim->ReloadMontage) || !IsAlive)
		return;



	Gun->Fire(GetMesh()->GetSocketLocation(TEXT("Muzzle")), false);
}

void AProjectOneCharacter::ReLoad()
{
	Gun->Reload();
}

void AProjectOneCharacter::UseItem1()
{
	Inventory->UseItem(0);
}

void AProjectOneCharacter::UseItem2()
{
	Inventory->UseItem(1);
}

void AProjectOneCharacter::UseItem3()
{
	Inventory->UseItem(2);
}

void AProjectOneCharacter::UseItem4()
{
	Inventory->UseItem(3);
}

void AProjectOneCharacter::UseItem5()
{
	Inventory->UseItem(4);
}

void AProjectOneCharacter::Win()
{
	ABLOG(Warning, TEXT("%s"), *GetName());
}

void AProjectOneCharacter::Lose()
{
}

void AProjectOneCharacter::Hit(float Damage, bool isHead, AActor * Causer)
{
	if (!Causer->IsA(ALauncherCharacter::StaticClass()) && Causer == this)
		return;

	if (isPause)
		return;
	//데미지계산식나중에 넣을것
	if (CharacterStat->CurHP - CalcDamage(Damage, isHead) <= 0) {
		CharacterStat->CurHP = 0;
		auto CauserPlayer = Cast<AProjectOneCharacter>(Causer);

		if (IsAlive && CauserPlayer)
		{
			CauserPlayer->Evolution();
			CauserPlayer->KillCount++;
		}

		IsAlive = false;

		GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
		GetMesh()->SetCollisionProfileName(TEXT("BlockAll"));
		GetMesh()->SetSimulatePhysics(true);
		GetWorld()->GetTimerManager().SetTimer(DeadTimer, this, &AProjectOneCharacter::Dead, 1.0f, true);

		auto AI = Cast<AAICharacter>(Causer);
		if (AI)
			AI->TargetPlayer = NULL;


		AProjectOneGameState* GameState = Cast<AProjectOneGameState>(UGameplayStatics::GetGameState(GetWorld()));
		GameState->AlivePlayers.Remove(this);

		//자기장에 사망했을 때
		auto ElectricField = Cast<AProjectOneGameState>(Causer);
		if (ElectricField)
		{
			// To do Something...
		}
	}
	else {

		if (!Causer)
			return;

		if (!Causer->IsA(AProjectOneGameState::StaticClass()))
		{
			isHit = true;
			LastHitByChracter = Causer;
		}

		CharacterStat->CurHP = CharacterStat->CurHP - CalcDamage(Damage, isHead);


		if (UGameplayStatics::GetPlayerPawn(GetWorld(), 0) == Causer
			&& Causer != this) {
			FName HitStr = "IsHit";

			AHUD* HUD = Cast<AHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
			UBoolProperty* isHit = FindField<UBoolProperty>(HUD->GetClass(), HitStr);

			if (HPBarWidgetComponent->GetUserWidgetObject())
				HPBarWidgetComponent->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Visible);

			if (isHit != NULL) {
				isHit->SetPropertyValue_InContainer(HUD, true);
			}

		}


		//플레이어가 유저이고 자기장에 데미지를 입었을 때
		auto ElectricField = Cast<AProjectOneGameState>(Causer);
		if (ElectricField && UGameplayStatics::GetPlayerPawn(GetWorld(), 0) == Causer)
		{
			FName CauserActor = "CausedActor";
			AHUD* HUD = Cast<AHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
			UObjectProperty* CausedAct = FindField<UObjectProperty>(HUD->GetClass(), CauserActor);

			if (CausedAct != NULL) {

				CausedAct->SetPropertyValue_InContainer(HUD, Causer);
			}


		}
	}

}

float AProjectOneCharacter::CalcDamage(float Damage, bool isHead)
{
	float reVal = Damage - (Damage * (CharacterStat->GetCharacterStatData()->AP / 100));
	if (isHead)
		reVal *= 1.25f;
	return reVal;
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
	if (isPause)
		return;

	if (Value) {
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;

	}
	//ABLOG(Warning,TEXT("Control:%d, val:%d, isroll:%d, "), (Controller != NULL), Value != 0.0f, !APAnim->isRoll)
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
	if (isPause)
		return;

	if (Value) {
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		if (Value == 1.0f)
			rollDir = RollDir::RIGHT;
		else if (Value == -1.0f)
			rollDir = RollDir::LEFT;
	}
	if ((Controller != NULL) && (Value != 0.0f) && !APAnim->isRoll)
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

void AProjectOneCharacter::Dead()
{
	DeadTime--;

	if (DeadTime < 1)
	{
		GetWorldTimerManager().ClearTimer(DeadTimer);
		Destroy(this);
	}
}

void AProjectOneCharacter::Evolution()
{
	CharacterStat->CurHP = CharacterStat->GetCharacterStatData()->HP;

	if (CurLevel > 5)
		return;
	EvolEffect->SetActive(true);
	switch (CurLevel)
	{
	case 0:
		GetMesh()->SetRelativeScale3D(FVector(1.0f));
		CameraBoom->SocketOffset = FVector(190.0f, 40.0f, 70.0f);
		//APAnim->ShotMontageCurrent = APAnim->ShotMontageFirst;
		break;
	case 1:
		GetMesh()->SetRelativeScale3D(FVector(1.2f));
		CameraBoom->SocketOffset = FVector(160.0f, 40.0f, 90.0f);
		break;
	case 2:
		GetMesh()->SetRelativeScale3D(FVector(1.5f));
		GetMesh()->SetSkeletalMesh(SecondSkMesh);
		CameraBoom->SocketOffset = FVector(100.0f, 50.0f, 90.0f);

		GetMesh()->SetAnimInstanceClass(SecondAnimIns);
		APAnim = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance());

		break;
	case 3:
		GetMesh()->SetRelativeScale3D(FVector(1.6f));
		break;
	case 4:
		GetMesh()->SetRelativeScale3D(FVector(1.7f));
		break;
	case 5:
		GetMesh()->SetSkeletalMesh(ThirdMesh);
		GetMesh()->SetRelativeScale3D(FVector(1.0f));

		GetMesh()->SetAnimInstanceClass(ThirdAnimIns);
		APAnim = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance());
		GetMesh()->SetRelativeScale3D(FVector(0.15f));

		//APAnim->ShotMontageCurrent = APAnim->ShotMontageThird;
		break;
	default:
		break;
	}
	++CurLevel;
	CharacterStat->SetCharacterID(CurLevel + (int)PlayerType);
	CharacterStat->SetWeaponeID(CurLevel + (int)PlayerType);
	CharacterStat->CurHP = CharacterStat->GetCharacterStatData()->HP;
}

void AProjectOneCharacter::CalcMagneticFieldDamage(float Damage)
{
	if (isPause)
		return;

	if (CharacterStat->CurHP - Damage <= 0) {
		CharacterStat->CurHP = 0;
		IsAlive = false;

		AProjectOneGameState* GameState = Cast<AProjectOneGameState>(UGameplayStatics::GetGameState(GetWorld()));
		GameState->AlivePlayers.Remove(this);

		GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
		GetMesh()->SetCollisionProfileName(TEXT("BlockAll"));
		GetMesh()->SetSimulatePhysics(true);
		GetWorld()->GetTimerManager().SetTimer(DeadTimer, this, &AProjectOneCharacter::Dead, 1.0f, true);

	}
	else
		CharacterStat->CurHP -= Damage;

}

