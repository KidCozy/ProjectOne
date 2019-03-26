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

	MaxBulletNum = 8;
	NowBulletNum = 8;
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



void AWeapon::Shot(FVector SpawnPos, FVector Direction)
{
	if (NowBulletNum > 0) {

		auto Bullet = GetWorld()->SpawnActor<ABullet>(SpawnPos, FRotator::ZeroRotator);
		if (Bullet != NULL) {
			Bullet->SetDirection(Direction);
			Bullet->Speed = 40.0f;
			Bullet->SetOwner(GetOwner());
		}
		NowBulletNum--;
	}


}

void AWeapon::ReLoad()
{
	NowBulletNum = MaxBulletNum;
}


