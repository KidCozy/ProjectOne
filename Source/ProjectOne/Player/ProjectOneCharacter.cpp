// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ProjectOneCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Weapons/Pistol.h"
#include "ProjectOne/Environments/GameModes/ProjectOneGameInstance.h"
#include "PlayerStatComponent.h"
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

	//static ConstructorHelpers::FObjectFinder<UBlueprint>EVOLUTION_START_MATERIAL(TEXT("MaterialInstanceConstant'/Game/Shaders/Dissolve/Barrier_Invert_Micro_Inst.Barrier_Invert_Micro_Inst'"));




	static ConstructorHelpers::FObjectFinder<UMaterialInstanceDynamic> EVOLUTION_START_MATERIAL(TEXT("MaterialInstanceConstant'/Game/Shaders/Dissolve/Barrier_Invert_Micro_Inst.Barrier_Invert_Micro_Inst'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstanceDynamic> EVOLUTION_END_MATERIAL(TEXT("MaterialInstanceConstant'/Game/Shaders/Dissolve/Barrier_Invert_Micro_Inst.Barrier_Invert_Micro_Inst'"));
	if(EVOLUTION_START_MATERIAL.Succeeded())
	{

		EVOLUTION_END_MATERIAL.Object->SetTextureParameterValue("BaseTexture", NULL);
		EVOLUTION_END_MATERIAL.Object->SetTextureParameterValue("MaskTexture", NULL);

		EVOLUTION_END_MATERIAL.Object->SetScalarParameterValue("Amount", 1.0f);
		EVOLUTION_END_MATERIAL.Object->SetScalarParameterValue("EmissiveAmount", 55.0f);
		EVOLUTION_END_MATERIAL.Object->SetScalarParameterValue("Fringe", 10.0f);
		EVOLUTION_END_MATERIAL.Object->SetScalarParameterValue("Offset", 3.5f);
		EVOLUTION_END_MATERIAL.Object->SetScalarParameterValue("TransitionTime", 3.0f);

		EVOLUTION_END_MATERIAL.Object->SetVectorParameterValue("GlowColor", FLinearColor::White);


		EVOLUTION_START_MATERIAL.Object->SetTextureParameterValue("BaseTexture", NULL);
		EVOLUTION_START_MATERIAL.Object->SetTextureParameterValue("MaskTexture", NULL);

		EVOLUTION_START_MATERIAL.Object->SetScalarParameterValue("Amount", 0.0f);
		EVOLUTION_START_MATERIAL.Object->SetScalarParameterValue("EmissiveAmount", 55.0f);
		EVOLUTION_START_MATERIAL.Object->SetScalarParameterValue("Fringe", 10.0f);
		EVOLUTION_START_MATERIAL.Object->SetScalarParameterValue("Offset", 3.5f);
		EVOLUTION_START_MATERIAL.Object->SetScalarParameterValue("TransitionTime", 3.0f);
		
		EVOLUTION_START_MATERIAL.Object->SetVectorParameterValue("GlowColor", FLinearColor::White);
		GetMesh()->SetMaterial(0, EVOLUTION_START_MATERIAL.Object);
		SecondMeshComponent->SetMaterial(0, EVOLUTION_END_MATERIAL.Object);

		ABLOG_S(Warning);
	}
	tmpLevel = 0;
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
	GetCapsuleComponent()->InitCapsuleSize(30.0f, 42.0f);
	
	APAnim = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	CharacterStat = CreateDefaultSubobject<UPlayerStatComponent>(TEXT("CharcterStat"));
	SecondMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Second Mesh"));
	SecondMeshComponent->SetupAttachment(RootComponent);
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
	CameraBoom->ProbeSize=20.0f;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	RayNearDistance = 500.0f;
	bIsOperateDamage = false;
	FollowCamera->SetRelativeLocation(FVector(-50.0f, 0, 0));

	CameraBoom->TargetArmLength = 350.0f;

	CameraBoom->SocketOffset = FVector(170.0f, 50.0f, 90.0f);

	InputVector = FVector::ZeroVector;
	Hp = 200.0f;
	MaxHp = Hp;
	IsAlive = true;
	DeadTime = 3;

	ItemSlot.Init((int32)Item::EMPTY, 2);

}

void AProjectOneCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Shot", IE_Pressed, this, &AProjectOneCharacter::Shot);
	PlayerInputComponent->BindAction("Shot", IE_Released, this, &AProjectOneCharacter::Shot);
	PlayerInputComponent->BindAction("testshot", IE_Pressed, this, &AProjectOneCharacter::Shot);
	PlayerInputComponent->BindAction("testshot", IE_Released, this, &AProjectOneCharacter::Shot);

	PlayerInputComponent->BindAction("ReLoad", IE_Pressed, this, &AProjectOneCharacter::ReloadAnimPlay);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AProjectOneCharacter::Aim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AProjectOneCharacter::Aim);

	//PlayerInputComponent->BindAction("Forward", IE_DoubleClick, this, &AProjectOneCharacter::ForwardDash);
	//PlayerInputComponent->BindAction("Back", IE_DoubleClick, this, &AProjectOneCharacter::BackDash);
	//PlayerInputComponent->BindAction("Left", IE_DoubleClick, this, &AProjectOneCharacter::LeftDash);
	//PlayerInputComponent->BindAction("Right", IE_DoubleClick, this, &AProjectOneCharacter::RightDash);
	PlayerInputComponent->BindAction("MoveInput", IE_Released, this, &AProjectOneCharacter::MoveReleased);

	PlayerInputComponent->BindAxis("MoveForward", this, &AProjectOneCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AProjectOneCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AProjectOneCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AProjectOneCharacter::LookUpAtRate);
	

	//PlayerInputComponent->BindTouch(IE_Pressed, this, &AProjectOneCharacter::TouchStarted);
	//PlayerInputComponent->BindTouch(IE_Released, this, &AProjectOneCharacter::TouchStopped);
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AProjectOneCharacter::OnResetVR);

	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &AProjectOneCharacter::Roll);
	PlayerInputComponent->BindAction("Evolution", IE_Pressed, this, &AProjectOneCharacter::Evolution);

	PlayerInputComponent->BindAction("Q", IE_Pressed, this, &AProjectOneCharacter::UseQItem);
	PlayerInputComponent->BindAction("E", IE_Pressed, this, &AProjectOneCharacter::UseEItem);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AProjectOneCharacter::JumpInput);
}


void AProjectOneCharacter::Tick(float delta) {
	Super::Tick(delta);
	if (isAim)
		GetFollowCamera()->SetFieldOfView(FMath::Lerp(GetFollowCamera()->FieldOfView, 60.0f, 0.1f));
	else
		GetFollowCamera()->SetFieldOfView(FMath::Lerp(GetFollowCamera()->FieldOfView, 100.0f, 0.1f));


	Shooting(delta);
	//SetScalarParameter(0,)
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

void AProjectOneCharacter::SetAmount()
{

}


void AProjectOneCharacter::SetTextureParameter(USkeletalMeshComponent* Comp,UINT Index, UTexture* Tex) {

	switch (Index) {
		case 0:
			Cast<UMaterialInstanceDynamic>(GetMesh()->GetMaterial(0))->SetTextureParameterValue("BaseTexture", Tex);
			break;
		case 1:
			Cast<UMaterialInstanceDynamic>(GetMesh()->GetMaterial(0))->SetTextureParameterValue("MaskTexture", Tex);
			break;
		default:
			return;
	}

}

void AProjectOneCharacter::SetScalarParameter(USkeletalMeshComponent*  Comp ,UINT MaterialIndex,UINT Index, float Value) {
	switch (Index) {
		case 0:
			Cast<UMaterialInstanceDynamic>(Comp->GetMaterial(MaterialIndex))->SetScalarParameterValue("Amount", Value);
			break;
		case 1:
			Cast<UMaterialInstanceDynamic>(Comp->GetMaterial(MaterialIndex))->SetScalarParameterValue("EmissiveAmount", Value);
			break;
		case 2:
			Cast<UMaterialInstanceDynamic>(Comp->GetMaterial(MaterialIndex))->SetScalarParameterValue("Fringe", Value);
			break;
		case 3:
			Cast<UMaterialInstanceDynamic>(Comp->GetMaterial(MaterialIndex))->SetScalarParameterValue("Offset", Value);
		case 4:
			break;
			Cast<UMaterialInstanceDynamic>(Comp->GetMaterial(MaterialIndex))->SetScalarParameterValue("TransitionTime", Value);
			break;
		default:
			return;
	}

	//ABLOG(Warning, TEXT("Name : %s  Value : %f"),*Comp->GetName() ,Value);
}

void AProjectOneCharacter::SetVectorParameter(USkeletalMeshComponent* Comp, UINT Index, FLinearColor Value) {

	switch (Index) {
		case 0:
			Cast<UMaterialInstanceDynamic>(Comp->GetMaterial(0))->SetVectorParameterValue("GlowColor", Value);
			break;
		default:
			return;
	}
}

void AProjectOneCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

//void AProjectOneCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
//{
//		Jump();
//}
//
//void AProjectOneCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
//{
//		StopJumping();
//}

void AProjectOneCharacter::Shot()
{
	if (!isShooting) {
		/*if (!APAnim->Montage_IsPlaying(APAnim->RollMontage)) {
			GetCharacterMovement()->MaxWalkSpeed = 450.0f;
		}*/
		intervalTime = 0;
		isShooting = true;
	}
	else {
		//GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		intervalTime = 0;
		isShooting = false;
	}
	APAnim->isShooting = isShooting;
}

void AProjectOneCharacter::Roll()
{
	if (CanRoll())
	{
		APAnim->isRoll = true;
		/*FRotator DirectionVec = InputVector.GetSafeNormal().Rotation() + FollowCamera->GetComponentRotation().GetNormalized();
		DirectionVec.Pitch = 0.0f;
		DirectionVec.Roll = 0.0f;
		GetCapsuleComponent()->SetRelativeRotation(DirectionVec);*/
		switch (rollDir)
		{
		case RollDir::FRONT:
			APAnim->Montage_Play(APAnim->F_RollMontage);
			break;
		case RollDir::BACK:
			APAnim->Montage_Play(APAnim->B_RollMontage);
			break;
		case RollDir::RIGHT:
			APAnim->Montage_Play(APAnim->R_RollMontage);
			break;
		case RollDir::LEFT:
			APAnim->Montage_Play(APAnim->L_RollMontage);
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
		//UKismetMathLibrary::FindLookAtRotation(FollowCamera->GetComponentLocation(), );
	}
	else {
		isAim = false;

		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}
}

void AProjectOneCharacter::ReloadAnimPlay()
{
	APAnim->Montage_Play(APAnim->ReloadMontage);
}

void AProjectOneCharacter::MoveReleased()
{
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//InputVector = FVector::ZeroVector;*/
	rollDir = RollDir::FRONT;
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
			if (Weapone->CurBulletCount <= 0) {
				APAnim->Montage_Stop(0.5f, APAnim->ShotMontage);
				APAnim->Montage_Stop(0.5f, APAnim->SecondShotMontage);
				return;
			}

			if (!APAnim->Montage_IsPlaying(APAnim->ShotMontage) && CanRoll()) 
			{
				APAnim->Montage_Play(APAnim->ShotMontage);
			}

			if (!APAnim->Montage_IsPlaying(APAnim->SecondShotMontage) && CanRoll()){
				APAnim->Montage_Play(APAnim->SecondShotMontage);
			}

			//Spread Bullet
			float RandPitch = FMath::RandRange(-(Weapone->Spread*0.5f), Weapone->Spread*0.5f);
			float RandYaw = FMath::RandRange(-(Weapone->Spread*0.5f), Weapone->Spread*0.5f);

			FVector TargetVector = GetCharacterToAimeVec();
			FRotator TargetRotation = TargetVector.Rotation();

			FRotator SpreadRotation = FRotator(
				TargetRotation.Pitch,// + RandPitch,
				TargetRotation.Yaw,// + RandYaw, 
				0.0f);

			//데미지 계산을 이미 GetCharacterToAimVec에서 시행했다면
			if (bIsOperateDamage) {
				bIsOperateDamage = false;
			}
			//아니면 총알발사
			else {
				switch (CurLevel %2) {
				case 0:

					Weapone->Shot(GetMesh()->GetSocketLocation(TEXT("Muzzle")), SpreadRotation, ScratchNormal);

					DrawDebugLine(GetWorld(), GetMesh()->GetSocketLocation(TEXT("Muzzle")),
						GetMesh()->GetSocketLocation(TEXT("Muzzle")), FColor::Red, false, 0.2f, 0, 1);
					break;
				case 1:
					Weapone->Shot(SecondMeshComponent->GetSocketLocation(TEXT("Muzzle")), SpreadRotation, ScratchNormal);
					break;
				}
			}
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

	else {
		APAnim->Montage_Stop(0.5f, APAnim->ShotMontage);
		APAnim->Montage_Stop(0.5f, APAnim->SecondShotMontage);
	}
}

void AProjectOneCharacter::ReLoad()
{
	Weapone->ReLoad();
}

void AProjectOneCharacter::SetItemSlot(int ItemNum)
{
	if (ItemSlot[0] == 0)
	{
		ItemSlot[0] = ItemNum;
	}
	else if (ItemSlot[1] == 0)
	{
		ItemSlot[1] = ItemNum;
	}
}

int AProjectOneCharacter::GetQItem()
{
	return ItemSlot[0];
}

int AProjectOneCharacter::GetEItem()
{
	return ItemSlot[1];
}

void AProjectOneCharacter::UseQItem()
{
	Item item = (Item)ItemSlot[0];
	switch (item)
	{
	case Item::EMPTY:
		break;
	case Item::EVOLUTION:
		ABLOG_S(Warning);
		ItemSlot[0] = 0;
		Evolution();
		break;
	case Item::HP:
		ItemSlot[0] = 0;
		if (Hp + 100 > MaxHp)
			Hp = MaxHp;
		else
			Hp += 100;
		break;
	default:
		break;
	}
}

void AProjectOneCharacter::UseEItem()
{
	Item item = (Item)ItemSlot[1];
	switch (item)
	{
	case Item::EMPTY:
		break;
	case Item::EVOLUTION:
		ItemSlot[1] = 0;
		Evolution();
		break;
	case Item::HP:
		ItemSlot[1] = 0;
		if (Hp + 100 > MaxHp)
			Hp = MaxHp;
		else
			Hp += 100;
		break;

	default:
		break;
	}
}

void AProjectOneCharacter::Hit(float Damage, AActor * Causer)
{
	if (Causer == this)
		return;

	if (Hp - Damage <= 0) {
		Hp = 0;
		auto CauserPlayer = Cast<AProjectOneCharacter>(Causer);
		if(IsAlive)
			CauserPlayer->Evolution();

		IsAlive = false;
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
		GetMesh()->SetCollisionProfileName(TEXT("BlockAll"));
		GetMesh()->SetSimulatePhysics(true);
		SecondMeshComponent->SetCollisionProfileName(TEXT("BlockAll"));
		SecondMeshComponent->SetSimulatePhysics(true);
		GetWorld()->GetTimerManager().SetTimer(DeadTimer, this, &AProjectOneCharacter::Dead, 1.0f, true);

		// AMyHUD * hud = Cast<AMyHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

		/* UFloatProperty* MyFloatProp = FindField<UFloatProperty>(AnimInst->GetClass(), AnimPropName);
			 if (MyFloatProp != NULL)
			 {
				float FloatVal = MyFloatProp->GetPropertyValue_InContainer(AnimInst);
				MyFloatProp->SetPropertyValue_InContainer(AnimInst, 180.0f);
				FloatVal = MyFloatProp->GetPropertyValue_InContainer(AnimInst);
			 }*/
			 /*UBoolProperty* BoolProp = FindField<UBoolProperty>(MyActor->GetClass(), PropName);
		  if (BoolProp != NULL)
		  {
			  bool BoolVal = BoolProp->GetPropertyValue_InContainer(Actor1);
			  BoolProp->SetPropertyValue_InContainer(Actor1, true);
		  }*/
		auto AI = Cast<AAICharacter>(Causer);
		if (AI)
			AI->TargetPlayer = NULL;
	}
	else {
		Hp = Hp - Damage;
	//	ABLOG_S(Warning);
		
		if (!Causer)
			return;
		if (!Causer->IsA(AAICharacter::StaticClass())) {
			FName HitStr = "IsHit";
			
			AHUD* HUD = Cast<AHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
			UBoolProperty* isHit = FindField<UBoolProperty>(HUD->GetClass(), HitStr);
			
			if (HPBarWidgetComponent->GetUserWidgetObject())
				HPBarWidgetComponent->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Visible);

			if (isHit != NULL) {
				ABLOG_S(Warning);

				isHit->SetPropertyValue_InContainer(HUD, true);
			}

		}
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
	if (Value) {
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		if (Value == 1.0f)
			rollDir = RollDir::FRONT;
		else if (Value == -1.0f)
			rollDir = RollDir::BACK;
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
	if (Value) {
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		if (Value == 1.0f)
			rollDir = RollDir::RIGHT;
		else if (Value == -1.0f)
			rollDir = RollDir::LEFT;
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
	FVector AimeStart = (CameraForwardVector*350.0f) + FollowCamera->GetComponentLocation();
	FVector AimEnd = (CameraForwardVector*10000.0f) + AimeStart;
	FCollisionQueryParams CameraCollisionParams;

	FVector tmpVec = AimEnd;

	if (GetWorld()->LineTraceSingleByChannel(OutHit, AimeStart, AimEnd, ECC_Pawn, CameraCollisionParams)) {
		tmpVec = OutHit.ImpactPoint;
		ScratchNormal = OutHit.Normal;

		//DrawDebugLine(GetWorld(), AimeStart, AimEnd, FColor::Blue, false, 1.0f, 0, 1.0f);
	}
	else
		ScratchNormal = FVector::ZeroVector;
	//DrawDebugLine(GetWorld(), AimeStart, AimEnd, FColor::Blue, false, 1.0f, 0, 1.0f);
	//적과의 거리가 카메라에서 RayNearDistance보다 가깝다면 데미지를 줌
	//if (FVector::Distance(tmpVec, FollowCamera->GetComponentLocation()) < RayNearDistance) {

	//	auto Character = Cast<AProjectOneCharacter>(OutHit.Actor);
	//	if (Character)
	//		Character->Hit(5.0f, GetOwner());

	//	auto AI = Cast<AAICharacter>(OutHit.Actor);
	//	if (AI)
	//		AI->Hit(10.0f, GetOwner());

	//	bIsOperateDamage = true;
	//}
	FVector reVal = FVector::ZeroVector;
	switch (CurLevel%2) {
	case 0:
		reVal = tmpVec - GetMesh()->GetSocketLocation(TEXT("Muzzle"));
		break;
	case 1:
		reVal = tmpVec - SecondMeshComponent->GetSocketLocation(TEXT("Muzzle"));
		break;
	}
	//drawline
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

void AProjectOneCharacter::CalcMagneticFieldDamage(float Damage)
{
	if (Hp - Damage <= 0) {
		Hp = 0;
		IsAlive = false;
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
		GetMesh()->SetCollisionProfileName(TEXT("BlockAll"));
		GetMesh()->SetSimulatePhysics(true);
		SecondMeshComponent->SetCollisionProfileName(TEXT("BlockAll"));
		SecondMeshComponent->SetSimulatePhysics(true);
		GetWorld()->GetTimerManager().SetTimer(DeadTimer, this, &AProjectOneCharacter::Dead, 1.0f, true);
	}
	else
		Hp-= Damage;
	
}

int32 AProjectOneCharacter::GetHP()
{
	return Hp;
}

int32 AProjectOneCharacter::GetMaxHP()
{
	return MaxHp;

}

int32 AProjectOneCharacter::GetMaxBullet()
{
	return Weapone->MaxBulletCount;
}

int32 AProjectOneCharacter::GetCurBullet()
{
	return Weapone->CurBulletCount;
}

int32 AProjectOneCharacter::GetEvolutionLevel()
{
	return tmpLevel;
}

bool AProjectOneCharacter::CanRoll()
{
	return (!APAnim->isRoll) ? true : false;
}

//void AProjectOneCharacter::ForwardDash()
//{
//	if (CanRoll())
//	{
//		GetCapsuleComponent()->SetRelativeRotation(
//			FRotator(0.0f, FollowCamera->GetComponentRotation().GetNormalized().Yaw, 0.0f)
//		);
//		APAnim->Montage_Play(APAnim->RollMontage);
//	}
//}
//
//void AProjectOneCharacter::BackDash()
//{
//	if (CanRoll())
//	{
//		GetCapsuleComponent()->SetRelativeRotation(
//			FRotator(0.0f, FollowCamera->GetComponentRotation().GetNormalized().Yaw - 180.0f, 0.0f)
//		);
//		APAnim->Montage_Play(APAnim->RollMontage);
//	}
//}
//
//void AProjectOneCharacter::LeftDash()
//{
//	if (CanRoll())
//	{
//		GetCapsuleComponent()->SetRelativeRotation(
//			FRotator(0.0f, FollowCamera->GetComponentRotation().GetNormalized().Yaw - 90.0f,0.0f)
//		);
//		APAnim->Montage_Play(APAnim->RollMontage);
//	}
//}
//
//void AProjectOneCharacter::RightDash()
//{
//	if (CanRoll())
//	{
//		GetCapsuleComponent()->SetRelativeRotation(
//			FRotator(0.0f, FollowCamera->GetComponentRotation().GetNormalized().Yaw + 90.0f, 0.0f)
//		);
//		APAnim->Montage_Play(APAnim->RollMontage);
//	}
//}