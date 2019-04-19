// Fill out your copyright notice in the Description page of Project Settings.

#include "Pistol.h"
#include "Bullet.h"

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	SetRootComponent(Mesh);

	MaxBulletCount = 100;
	CurBulletCount = 100;
	Spread = 1.0f;
	IntervalTime = 0.06f;
	Range = 100.0f;
	VerticalRecoil = 0.15f;
	HorizonRecoil = 0.1f;
}

void AWeapon::InitWeapone(int maxBullet, float verticalRecoil, float horizonRecoil, float spread, float reloadDelay, float bulletSpeed, float range)
{
	MaxBulletCount = maxBullet;
	CurBulletCount = MaxBulletCount;
	VerticalRecoil = verticalRecoil;
	HorizonRecoil = horizonRecoil;
	Spread = spread;
	ReloadDelay = reloadDelay;
	Speed = bulletSpeed;
	Range = range;
	
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::Shot(FVector SpawnPos, FRotator Direction, FVector Nolmal)
{
	if (CurBulletCount > 0) {

		auto Bullet = GetWorld()->SpawnActor<ABullet>(SpawnPos, Direction);
		if (Bullet != NULL) {
			//Bullet->SetDirection(Direction);
			Bullet->Speed = Speed;
			Bullet->SetOwner(GetOwner());
			Bullet->Normal = Nolmal;
		}
		CurBulletCount--;
	}
}


void AWeapon::ReLoad()
{
	CurBulletCount = MaxBulletCount;
}