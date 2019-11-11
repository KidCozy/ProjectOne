// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "GameFramework/Actor.h"
#include "Explosion.generated.h"

UCLASS()
class PROJECTONE_API AExplosion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosion();

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereCollision;
	
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ExplosionParticle;
	
	void ActiveExplosion(FVector SpawnPosition);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void DestroyActor();

protected:

	FTimerHandle DestroyTimer;
};
