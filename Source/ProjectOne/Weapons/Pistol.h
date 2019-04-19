// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "GameFramework/Actor.h"
#include "Pistol.generated.h"

UCLASS()
class PROJECTONE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//최대 탄창, 수직반동, 좌우반동, 탄퍼짐, 재장전 시간, 사정거리
	void InitWeapone(int maxBullet, float verticalRecoil, float horizonRecoil, float spread, float reloadDelay,float bulletSpeed, float range);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void Shot(FVector SpawnPos, FRotator Direction, FVector Normal);

	void ReLoad();

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent * Mesh;

	UPROPERTY()
	int CurBulletCount;

	UPROPERTY()
	int MaxBulletCount;

	UPROPERTY()
	float ReloadDelay;

	UPROPERTY()
	float IntervalTime;

	UPROPERTY()
	float Range;

	UPROPERTY(EditAnywhere)
	float Spread;

	UPROPERTY(EditAnywhere)
	float VerticalRecoil;

	UPROPERTY(EditAnywhere)
	float HorizonRecoil;

	UPROPERTY(EditAnywhere)
	float Speed;
};
