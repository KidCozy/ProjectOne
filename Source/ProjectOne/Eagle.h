// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "GameFramework/Actor.h"
#include "Eagle.generated.h"

UCLASS()
class PROJECTONE_API AEagle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEagle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent * Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Speed)
	float Speed; //¹ÝÁö¸§

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Turn)
	bool bTurn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Speed)
	bool bCheck;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Turn)
	float Angle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Turn)
	float TurnSpeed;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
