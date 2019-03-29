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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnCollisionOverlap(UPrimitiveComponent * OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OherCcomp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	void SetDirection(FVector direction);

protected:
	UPROPERTY(VisibleAnywhere, Category = Col)
	USphereComponent * Col;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent * Mesh;

};