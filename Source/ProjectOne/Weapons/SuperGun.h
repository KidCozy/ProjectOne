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
	//������
	void Reload();
	//�߻�
	virtual void Fire(FVector MuzzlePos, bool isAI);
	//����ӵ�Ÿ�̸�
	void RefireCheck();
	//���ӹ������� ���� ���⺤�͸� ���ϴ� �Լ�
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
