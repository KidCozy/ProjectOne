// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "Player/ProjectOneCharacter.h"
#include "Cover.h"
#include "AICharacter.generated.h"

enum MoveVec
{
	ForwardVec,
	LeftVec,
	RightVec
};

enum AIState
{
	Neutral,
	Offensive,
	Diffensive
};

/**
 * 
 */
UCLASS()
class PROJECTONE_API AAICharacter : public AProjectOneCharacter
{
	GENERATED_BODY()


public:
	AAICharacter();
	virtual void PostInitializeComponents() override;
	virtual void Tick(float delta) override;
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	class AProjectOneAIController * AICon;

	void Forward();
	void Back();
	void Left();
	void RIght();

	void LookAt(FVector LookPos);


	void Detected();
	void CheckObstacle();

	AProjectOneCharacter * TargetPlayer;
	ACover * TargetCover;
	FVector TargetCoverPos;

	FVector TargetLocationPos;
	bool CheckLocation(FVector Pos);

	TArray<AProjectOneCharacter*> DetectedPlayers;
	TArray<ACover*> DetectedCovers;
	TArray<ACover*> PastCovers;

	MoveVec DirectionVec;
	bool FirstCheck;
	bool IsMoving;

	FTimerHandle  Delay;

	bool IsLookAround;
	bool LeftEnd;
	float LeftAngle;
	float RightAngle;

	void LookAround();
	void LookAroundStart();

	virtual void Shooting(float tick) override;
	FVector Prediction();

	AIState CurState;

	void Update();

	void MoveCover();//���买�� �̵�
	void NextCover();//���买 ����
	void NextCover(FVector Destination);
	void CheckSafe();//���买 ��������
	void CheckSafe(FVector Destination);

	bool IsLookTarget;

	void MoveToLocation(FVector Location);

	void Hide(AActor * Attacker);

};

