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
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void Shot(FVector SpawnPos,FVector Direction);

	void ReLoad();

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent * Mesh;

	UPROPERTY()
	int NowBulletNum;
	
	UPROPERTY()
	int MaxBulletNum;
};
