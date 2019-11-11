// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperGun.h"
#include "Player/POComponents/PlayerStatComponent.h"
#include "Bullet.h"
#include "Player/ProjectOneCharacter.h"
#include "Player/POComponents/POPlayerAkComponent.h"
#include "ProjectOne/Environments/GameModes/ProjectOneGameInstance.h"

// Sets default values for this component's properties
USuperGun::USuperGun()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	PrimaryComponentTick.bCanEverTick = false;
	Owner = Cast<AProjectOneCharacter>(GetOwner());
	CanShot = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> SHOOT(TEXT("ParticleSystem'/Game/Action_FX/ParticleSystems/MuzzleFlash/P_MuzzleFlash1.P_MuzzleFlash1'"));
	if (SHOOT.Succeeded()) {
		ShootEffect = SHOOT.Object;
	}

	SoundManager = CreateDefaultSubobject<UPOPlayerAkComponent>(TEXT("Sound"));
	SoundManager->SetupAttachment(this);
	// ...
}

void USuperGun::Reload()
{
	ABLOG(Warning, TEXT("%d"), Owner->CharacterStat->GetWeaphoneStatData()->MaxBullet);
	CurBullet = Owner->CharacterStat->GetWeaphoneStatData()->MaxBullet;
}

void USuperGun::Fire(FVector MuzzlePos, bool isAI)
{
	if (!CanShot)
		return;
	CanShot = false;

	//연사속도 타이머 설정
	float CSSpeed = 0;
	if (Owner->CharacterStat->GetWeaphoneStatData() != nullptr)
		CSSpeed = Owner->CharacterStat->GetWeaphoneStatData()->CSSpeed;
	GetWorld()->GetTimerManager().SetTimer(CSTimer, this, &USuperGun::RefireCheck, CSSpeed, true, CSSpeed);

	//애니메이션 종료
	if (CurBullet <= 0)
	{
		Owner->APAnim->Montage_Stop(0.5f, Owner->APAnim->ShotMontage);
		return;
	}

	//애니메이션 실행
	if (!Owner->APAnim->Montage_IsPlaying(Owner->APAnim->ShotMontage)
		&& !Owner->APAnim->isRoll)
	{
		Owner->APAnim->Montage_Play(Owner->APAnim->ShotMontage);
	}



	//카메라 쉐이크
	if (!isAI)
	{
		auto GameInstance = Cast<UProjectOneGameInstance>(Owner->GetGameInstance());
		GameInstance->HitShake(GameInstance->CShakePistol, 1.0f);
	}
	//이펙트 출력
	FTransform FireEffectTransform = Owner->GetMesh()->GetSocketTransform(TEXT("Muzzle"));
	FireEffectTransform.SetScale3D(FVector(0.25f, 0.25f, 0.25f));

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ShootEffect, FireEffectTransform);

	//사운드 출력
	SoundManager->PlayPistolShotSound();

	FRotator SpreadRotation = GetAimVector(MuzzlePos).Rotation();

	//if (isAI) {

	//}

	float spreadVal = 3.0f;
	float RandPitch = FMath::RandRange(-(spreadVal*0.5f*1.5f), spreadVal*0.5f*1.5f);
	float RandYaw = FMath::RandRange(-(spreadVal*0.5f*1.5f), spreadVal*0.5f*1.5f);

	SpreadRotation = FRotator(
		SpreadRotation.Pitch + RandPitch,
		SpreadRotation.Yaw + RandYaw, 0.0f);


	//총알생성
	auto Bullet = GetWorld()->SpawnActor<ABullet>(MuzzlePos, SpreadRotation);
	if (Bullet)
	{
		Bullet->SetDirection(GetAimVector(MuzzlePos));
		Bullet->SetStartPos(MuzzlePos);
		Bullet->SetOwner(Owner);
	}
	CurBullet--;

	//총반동
	float PitchVal = FMath::RandRange(0.15f * 0.7f, 0.15f);
	float YawVal = FMath::RandRange(-0.1f * 0.5f, 0.1f*0.5f);

	Owner->AddControllerPitchInput(-PitchVal);
	Owner->AddControllerYawInput(YawVal);

}

void USuperGun::RefireCheck()
{
	CanShot = true;
	Owner->GetWorldTimerManager().ClearTimer(CSTimer);
}


int USuperGun::GetMaxBullet()
{
	return Owner->CharacterStat->GetWeaphoneStatData()->MaxBullet;
}

int USuperGun::GetCurBullet()
{
	return CurBullet;
}

void USuperGun::BeginPlay()
{
	Super::BeginPlay();
	if(Owner->CharacterStat->GetWeaphoneStatData())
	CurBullet = Owner->CharacterStat->GetWeaphoneStatData()->MaxBullet;
}


void USuperGun::ChangeWeapon(int WeaponNum)
{
	Owner->CharacterStat->SetWeaponeID(WeaponNum);
}

FVector USuperGun::GetAimVector(FVector StartPos)
{
	FHitResult OutHit;
	FVector CameraForwardVector = Owner->FollowCamera->GetComponentRotation().Vector();
	FVector AimeStart = (CameraForwardVector*350.0f) + Owner->FollowCamera->GetComponentLocation();
	FVector AimEnd = (CameraForwardVector*10000.0f) + AimeStart;
	FCollisionQueryParams CameraCollisionParams;

	FVector tmpVec = AimEnd;

	if (GetWorld()->LineTraceSingleByChannel(OutHit, AimeStart, AimEnd, ECC_Pawn, CameraCollisionParams)) {
		tmpVec = OutHit.ImpactPoint;

	}

	FVector reVal = FVector::ZeroVector;
	reVal = tmpVec - StartPos;

	return reVal.GetSafeNormal();
}
