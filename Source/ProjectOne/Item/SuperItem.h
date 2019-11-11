// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "GameFramework/Actor.h"
#include "SuperItem.generated.h"

class AProjectOneCharacter;

UCLASS()
class PROJECTONE_API ASuperItem : public AActor
{
	GENERATED_BODY()
protected:

	UPROPERTY(VisibleAnywhere, Category = Col)
	USphereComponent * Col;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* Particle1;

	UPROPERTY(VisibleAnywhere)
	UParticleSystem* UseEffect;

	AProjectOneCharacter* ItemOwner;

	FTimerHandle DurationTimer;

	uint8 DurationTime;
public:

	virtual void Use() { ABLOG(Warning, TEXT("Please Make UseFunction")); }

	ASuperItem();

	void SetNewOwner(AProjectOneCharacter* NewOwner) { ItemOwner = NewOwner; }
	
	UFUNCTION()
	void OnCollisionOverlap(UPrimitiveComponent * OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OherCcomp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UPROPERTY(VisibleAnywhere)
	E_Item eItem;

protected:	
	virtual void BeginPlay() override;
	virtual void InitAssets();
	void Duration();
	virtual void DurationEnd() {}
};
