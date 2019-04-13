// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ProjectOne.h"
#include "Animation/PlayerCharacterAnimInstance.h"
#include "GameFramework/Character.h"
#include "ProjectOneCharacter.generated.h"

UCLASS(config=Game)
class AProjectOneCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */

public:
	AProjectOneCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
	
	UPROPERTY()
	class AWeapon * Weapone;

	UPROPERTY(VisibleAnywhere)
	class APlayerSoundManager* SoundManager;

	UPROPERTY()
	float Hp;

	void Hit(float Damage, AActor * Causer);

protected: // protected �Լ� ����
	
	// ������, �ʱ�ȭ
	virtual void SetResources(); // ���ҽ� �ε� (�ʱ�ȭ)
	virtual void SetInitWeapone();

	// �ƹ� ������� VR�ڵ�
	void OnResetVR();
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	// ���� �Լ�
	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	// �׼� �Լ�
	void Shot();
	void Roll();
	void ForwardDash();
	void BackDash();
	void LeftDash();
	void RightDash();
	void MoveReleased();
	void JumpInput();

	// ȭ��FX
	void PlayCShake(int Index);
	
	virtual void Shooting(float tick);

	void ReLoad();
	void Evolution();
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
	// End of APawn interface

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
	bool CanRoll();

private:
	float intervalTime = 0.0f;
	FVector InputVector;
	FVector ScratchNormal;
};

