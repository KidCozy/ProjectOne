// Fill out your copyright notice in the Description page of Project Settings.

#include "Explosion.h"
#include "Player/ProjectOneCharacter.h"
#include "DrawDebugHelpers.h"
#include "AI/AICharacter.h"

// Sets default values
AExplosion::AExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	ExplosionParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));

	RootComponent = SphereCollision;
	SphereCollision->InitSphereRadius(60.0f);
	SphereCollision->SetCollisionProfileName(TEXT("Bullet"));
	ExplosionParticle->SetRelativeLocation(FVector::ZeroVector);
	ExplosionParticle->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleObj(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_explosion1.P_ky_explosion1'"));
	if (ParticleObj.Succeeded()) 
	{
		ExplosionParticle->SetTemplate(ParticleObj.Object);
	}
}

// Called when the game starts or when spawned
void AExplosion::BeginPlay()
{
	Super::BeginPlay();
}


void AExplosion::ActiveExplosion(FVector SpawnPosition)
{

	SetActorLocation(SpawnPosition);
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	bool bResult = GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		SpawnPosition,
		FQuat::Identity,
		ECollisionChannel::ECC_Pawn,
		FCollisionShape::MakeSphere(60.0f),
		CollisionQueryParam
	);
	if(bResult)
	{
		for (auto OverlapResult : OverlapResults)
		{
			if (OverlapResult.Actor->IsA(AProjectOneCharacter::StaticClass())) 
			{
				Cast<AProjectOneCharacter>(OverlapResult.Actor)->Hit(5.0f, false, GetOwner());
			}
		}
	}
	DrawDebugSphere(GetWorld(), SpawnPosition, 60.0f,10, FColor::Red,false,1.0f);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle->Template, GetActorLocation());
	GetWorld()->GetTimerManager().SetTimer(DestroyTimer, this, &AExplosion::DestroyActor, 0.5f, true, 0.5f);
}

void AExplosion::DestroyActor()
{
	GetWorldTimerManager().ClearTimer(DestroyTimer);
	Destroy();
}
