// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "GameFramework/Actor.h"
#include "EvolutionItem.generated.h"

UCLASS()
class PROJECTONE_API AEvolutionItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEvolutionItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(VisibleAnywhere, Category = Col)
	USphereComponent * Col;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent * Mesh;

	UFUNCTION()
	void OnCollisionOverlap(UPrimitiveComponent * OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OherCcomp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	void Drop();

	int ItemNum;

};
