// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "ProjectOneGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FPOCharcacterData :public FTableRowBase
{
	GENERATED_BODY()
public:
	FPOCharcacterData():ID(1), HP(100.0f), Speed(600.f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Speed;
};

USTRUCT(BlueprintType)
struct FPOWeaponeData :public FTableRowBase
{
	GENERATED_BODY()
public:
	FPOWeaponeData(): ID(1), Damage(15.f),Shooting_interval(0.06f), Range(25.f),Spread(1.f),Vertical_recoil(1.f),Horizon_recoil(1.f), Bullet_Speed(1.f),Reload_speed(2.f),Magazine(15) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Shooting_interval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Spread;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Vertical_recoil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Horizon_recoil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Bullet_Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Reload_speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Magazine;
};

/**
 * 
 */
UCLASS()
class PROJECTONE_API UProjectOneGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UCameraShake> CShakePistol;

	UProjectOneGameInstance(const FObjectInitializer& ObjectInitializer);
	FPOCharcacterData* GetCharcterData(int32 name);
	FPOWeaponeData* GetWeaponData(int32 name);
	virtual void Init() override;
	void HitShake(TSubclassOf<UCameraShake> CShake, float Scalar);

private:
	class UDataTable* CharacterTable;
	class UDataTable* WeaponeTable;
};
