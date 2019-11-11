// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include "AI/AICharacter.h"
#include "Explosion.h"
#include "Kismet/GamePlayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectOne/Player/POComponents/POPlayerAkComponent.h"


// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Col = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	Trail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail"));
	Hit = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Hit"));

	RootComponent = Col;

	Trail->SetupAttachment(RootComponent);
	Hit->SetupAttachment(RootComponent);
	Trail->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	Hit->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	Col->SetSphereRadius(50.0f);
	Speed = 70.0f;

	Col->SetCollisionProfileName(TEXT("Bullet"));

	DirectionVector = GetActorForwardVector();
	SetActorScale3D(FVector(0.2f, 0.05f, 0.05f));
	SetActorScale3D(GetActorScale()*1.0f);

	static ConstructorHelpers::FObjectFinder<UMaterial> MATERIAL(TEXT("Material'/Game/Materail/NewMaterial.NewMaterial'"));

	if (MATERIAL.Succeeded()) {
		Material = MATERIAL.Object;
	}


	static ConstructorHelpers::FObjectFinder<UParticleSystem> TRAIL(TEXT("ParticleSystem'/Game/Action_FX/ParticleSystems/Magic_Bullet/Bullet.Bullet'"));
	if (TRAIL.Succeeded()) {
		Trail->SetTemplate(TRAIL.Object);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> HIT(TEXT("ParticleSystem'/Game/Action_FX/ParticleSystems/MuzzleFlash/P_Hit_1Spawn.P_Hit_1Spawn'"));
	if (HIT.Succeeded()) {
		Hit->SetTemplate(HIT.Object);
	}



	static ConstructorHelpers::FObjectFinder<UMaterialInstance> ScratchMatObj(TEXT("MaterialInstanceConstant'/Game/Materail/BulletScratch_Decal_Inst.BulletScratch_Decal_Inst'"));
	if(ScratchMatObj.Succeeded())
	{
		DecalMaterialinstance = ScratchMatObj.Object;
	}


	SoundManager = CreateDefaultSubobject<UPOPlayerAkComponent>(TEXT("Sound"));
	SoundManager->SetupAttachment(RootComponent);

	Hit->DeactivateSystem();
	Hit->SetVisibility(false);
	//Trail->AutoAttachSocketName = TEXT("Middle");


	isStartRay = true;
	isHit = false;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->InitialSpeed = 50000.0f;
	LifeTime = 0.0f;

}

void ABullet::SetStartPos(FVector Position)
{
	PreLocation = Position;
}


void ABullet::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//   Col->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnCollisionOverlap);
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	Explosion = Cast<AExplosion>(GetWorld()->SpawnActor<AExplosion>(FVector(0.0f), GetActorRotation()));
	Explosion->SetOwner(GetOwner());
	//GetWorld()->GetTimerManager().SetTimer(RayCheckTimer, this, &ABullet::RayCheckFunc, 0.1f, true);
	//Weapone->Shot(GetMesh()->GetSocketLocation(TEXT("Muzzle")), SpreadRotation, ScratchNormal);
}
// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult OutHit;
	FVector StartRay = GetActorLocation();
	FVector EndRay = (DirectionVector * 1000.0f) + GetActorLocation();
	FCollisionQueryParams CollisionParam;
	if (isStartRay) {
		StartRay = PreLocation;
		isStartRay = false;
	}

	if (GetWorld()->LineTraceSingleByChannel(OutHit, StartRay, EndRay, ECC_Pawn, CollisionParam)) {
		if (!isHit) {
			Trail->SetActive(false);
			isHit = true;

			auto Character = Cast<AProjectOneCharacter>(OutHit.Actor);
			if (Character)
			{
				bool isHeadShot = "Bip001-Head" == OutHit.BoneName;
				Character->Hit(5.0f, isHeadShot, GetOwner());
			}

			auto AI = Cast<AAICharacter>(OutHit.Actor);
			if (AI)
			{
				bool isHeadShot = "Bip001-Head" == OutHit.BoneName;
				AI->Hit(10.0f, isHeadShot, GetOwner());
			}

			if (!Character && !AI)
				SoundManager->PlayBulletCrashSound();


			//플레이어가 launcher면
			if(Cast<AProjectOneCharacter>(GetOwner())->PlayerType == E_PlayerSelect::E_LAUNCHER)
			{
				Explosion->SetOwner(GetOwner());
				Explosion->ActiveExplosion(OutHit.Location);
				
			}
			else 
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Hit->Template, OutHit.Location);
				UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterialinstance,
					FVector(30.0f, 5.0f, 5.0f), OutHit.Location,
					OutHit.ImpactNormal.Rotation(), 100.0f);
			}
		
		}
	}

	//DrawDebugLine(GetWorld(), StartRay, EndRay, FColor::Red, false, 1.0f, 0, 1);
	LifeTime += DeltaTime;



	if (LifeTime > 5.0f)
		Destroy();


}
//
//void ABullet::OnCollisionOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OherCcomp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
//{
//   ABLOG_S(Warning);
//   ABCHECK(GetOwner());
//   //CreateDecal
//   
//   UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterialinstance,
//         FVector(30.0f, 5.0f, 5.0f), this->GetActorLocation(),
//      Normal.Rotation(), 100.0f);
//
//   
//   ABLOG(Warning, TEXT("Owner : %s"), *(GetOwner()->GetName()));
//   ABLOG(Warning, TEXT("OtherActor : %s"), *(OtherActor->GetName()));
//
//   //ABCHECK(IsValid(Cast<AProjectOneCharacter>(OtherActor)));
//   auto Character = Cast<AProjectOneCharacter>(OtherActor);
//   if (Character)
//      Character->5.0f, GetOwner());
//
//   //ABCHECK(IsValid(Cast<AAICharacter>(OtherActor)));
//   auto AI = Cast<AAICharacter>(OtherActor);
//   if (AI)
//      AI->Hit(10.0f, GetOwner());
//
//
//
//   Destroy(this);
//
//}

void ABullet::SetDirection(FVector direction)
{
	DirectionVector = direction;
	SetActorRotation(direction.Rotation());
}
