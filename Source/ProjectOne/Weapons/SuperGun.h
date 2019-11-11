// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "Components/SceneComponent.h"
#include "SuperGun.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTONE_API USuperGun : public USceneComponent
{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties
	USuperGun();
public:	
	//재장전
	void Reload();
	//발사
	virtual void Fire(FVector MuzzlePos, bool isAI);
	//연사속도타이머
	void RefireCheck();
	//에임방향으로 가는 방향벡터를 구하는 함수
	FVector GetAimVector(FVector StartPos);

public:
	UFUNCTION(BlueprintCallable)
	int GetMaxBullet();
	
	UFUNCTION(BlueprintCallable)
	int GetCurBullet();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void ChangeWeapon(int WeaponNum);

protected:
	UPROPERTY(VisibleAnywhere)
	class AProjectOneCharacter* Owner;

	UPROPERTY(EditAnywhere, Category = Effect)
	UParticleSystem* ShootEffect;

	UPROPERTY(VisibleAnywhere, Category = Sound)
	class UPOPlayerAkComponent* SoundManager;

	FTimerHandle CSTimer;
	int CurBullet;
	bool CanShot;
};
