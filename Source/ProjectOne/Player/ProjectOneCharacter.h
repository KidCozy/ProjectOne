// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ProjectOne.h"
#include "Animation/PlayerCharacterAnimInstance.h"
#include "GameFramework/Character.h"
#include "Environments/ShaderInfo.h"
#include"Kismet/KismetMathLibrary.h"
#include "ProjectOneCharacter.generated.h"


UCLASS(config=Game)
class AProjectOneCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
protected:
	enum class RollDir {
		FRONT,
		BACK,
		LEFT,
		RIGHT
	};
public:
	AProjectOneCharacter(); 

	UPROPERTY()
	TArray<UMaterialInstance*> ShaderInstance;

	UPROPERTY()
	TArray<UMaterialInstanceDynamic*> DynamicShader;

	UPROPERTY()
	TArray<UMaterialInterface*> Mat;
	//���峡���� �պ���
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SecondMeshComponent;

	UPROPERTY(VisibleAnywhere)
	USkeletalMesh* ThirdMesh;

	//��ȭ
	UPROPERTY(VisibleAnywhere)
	class USkeletalMesh* SecondSkMesh;

	UPROPERTY(VisibleAnywhere)
	class UClass* SecondAnimIns;

	UPROPERTY(VisibleAnywhere)
	class UClass* ThirdAnimIns;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
	
	UPROPERTY()
	class AWeapon* Weapone;

	UPROPERTY()
	float Hp;

	UPROPERTY()
	float MaxHp;

	void Hit(float Damage, AActor * Causer);

	bool IsAlive;

	UINT EvolutionLevel = 0;

	FTimerHandle DeadTimer;

	int DeadTime;

	virtual void Evolution();

	UFUNCTION(BlueprintCallable)
	int32 GetHP();

	UFUNCTION(BlueprintCallable)
	int32 GetMaxHP();

	UFUNCTION(BlueprintCallable)
	int32 GetMaxBullet();

	UFUNCTION(BlueprintCallable)
	int32 GetCurBullet();

	UFUNCTION(BlueprintCallable)
	int32 GetEvolutionLevel();

protected: // protected �Լ� ����
	
	// ������, �ʱ�ȭ
	virtual void SetResources(); // ���ҽ� �ε� (�ʱ�ȭ)
	virtual void SetComponents();
	virtual void SetInitWeapone();

	virtual void SetTextureParameter(USkeletalMeshComponent* Comp, UINT Index, UTexture* Tex);
	virtual void SetScalarParameter(USkeletalMeshComponent* Comp,UINT MaterialIndex, UINT ParameterIndex, float Value);
	virtual void SetVectorParameter(USkeletalMeshComponent* Comp, UINT Index, FLinearColor Value);

	virtual bool GetDissolveAmount(UMaterialInstance* Inst, float& OutValue) const { return Inst->GetScalarParameterValue(FMaterialParameterInfo("Amount"), OutValue); }

	// �ƹ� ������� VR�ڵ�
	void OnResetVR();
	//void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	//void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	// ���� �Լ�
	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	// �׼� �Լ�
	void Shot();
	void Roll();
	void Aim();

	//virtual void ForwardDash();
	//virtual void BackDash();
	//virtual void LeftDash();
	//virtual void RightDash();

	void MoveReleased();
	void JumpInput();

	// ȭ��FX
	void PlayCShake(int Index);
	
	virtual void Shooting(float tick);

	void ReLoad();

	void Dead();
	FVector GetCharacterToAimeVec();
protected: // protected �ڿ� ����
	
	// ����
	const UWorld* const World = GetWorld(); 

	APlayerController* PlayerController;

	UPROPERTY(VisibleAnywhere)
	class UPlayerCharacterAnimInstance* APAnim;

	UPROPERTY(VisibleAnywhere)
	TArray<TSubclassOf<UCameraShake>> CShakeList;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UPlayerStatComponent* CharacterStat;


	UPROPERTY()
	bool isShooting;



protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	virtual void Tick(float delta) override;
	virtual void BeginPlay() override;
	virtual void SetAmount();
	// End of APawn interface

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


private:
	bool CanRoll();

protected:
	float intervalTime = 0.0f;
	//�� ������ �� �Ÿ����� ������ �Ѿ��� �����ʰ� �������� �ִ� ����
	float RayNearDistance;
	//���̷� �������� �̹� ó�� �Ǿ���?
	bool bIsOperateDamage;
	int32 CurLevel;
	FVector InputVector;
	FVector ScratchNormal;
	float curAmount = 0.0f;
	float SecCurAmount = 0.5f;
	FTimerHandle EvolutionTimer;
	RollDir rollDir;
	bool isAim;
};

