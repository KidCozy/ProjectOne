// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "GameFramework/Actor.h"
#include "Pistol.generated.h"

UCLASS()
class PROJECTONE_API APistol : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APistol();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class ABullet * Bullet;

	void Shot(FVector direction);

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent * Mesh;
};
