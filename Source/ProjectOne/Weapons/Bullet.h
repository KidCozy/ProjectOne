// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class PROJECTONE_API ABullet : public AActor
{
	GENERATED_BODY()

	public:
	// Sets default values for this actor's properties
	ABullet();

	UPROPERTY(EditInStanceOnly, Category = Stat)
	float Speed;

	FVector DirectionVector;

	FVector Normal;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay()override;

	void SetStartPos(FVector Position);

	//void RayCheckFunc();
	/*UFUNCTION()
	void OnCollisionOverlap(UPrimitiveComponent * OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OherCcomp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
 */
	void SetDirection(FVector direction);

protected:
	UPROPERTY(VisibleAnywhere, Category = Col)
	USphereComponent * Col;

	UPROPERTY(VisibleAnywhere, Category = MoveMent)
	UProjectileMovementComponent * ProjectileMovement;

	UPROPERTY(VisibleAnywhere, Category = Matareal)
	UMaterial * Material;

	UPROPERTY(VisibleAnywhere, Category = Matareal)
	UMaterialInstanceDynamic * Materialinstance;

	UPROPERTY(EditAnywhere, Category = Scratch)
	UParticleSystemComponent* Trail;

	UPROPERTY(EditAnywhere, Category = Scratch)
	UParticleSystemComponent* Hit;

	UPROPERTY(VisibleAnywhere, Category = Sound)
	class UPOPlayerAkComponent* SoundManager;

	UPROPERTY(VisibleAnywhere, Category = Matareal)
	UMaterialInstance * DecalMaterialinstance;

	class AExplosion* Explosion;

	//FTimerHandle RayCheckTimer;
	FVector PreLocation;

	float LifeTime;

	bool isStartRay;
	//월샷 없애기 용
	bool isHit;
};