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
	FPOCharcacterData():ID(1), HP(100.0f), AP(1.f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float AP;
};

USTRUCT(BlueprintType)
struct FPOWeaponeData :public FTableRowBase
{
	GENERATED_BODY()
public:
	FPOWeaponeData(): ID(1), Damage(15.f), Range(25.f), ReboundRateX(1.f), ReboundRateY(1.f),BulletSpeed(1.f),MaxBullet(15), CSSpeed(0.06f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float ReboundRateX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float ReboundRateY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float BulletSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 MaxBullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float CSSpeed;
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerWeapon")
	E_PlayerSelect PlayerType;
	//FString PlayerWeapone;	


private:
	class UDataTable* CharacterTable;
	class UDataTable* WeaponeTable;
};
