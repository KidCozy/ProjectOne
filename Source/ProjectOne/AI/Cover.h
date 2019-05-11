// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "GameFramework/Actor.h"
#include "Cover.generated.h"

UCLASS()
class PROJECTONE_API ACover : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACover();

protected:

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent * Mesh;



	virtual void BeginPlay() override;

public:	

	TArray<FVector> SafePos;

};
