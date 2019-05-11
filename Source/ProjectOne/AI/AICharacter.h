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
	Diffensive,
	Guard,
	Dead
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

	void SetResources() override;
	void Evolution() override;
	void SetAmount() override;

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

	float Distance(FVector Vec1, FVector Vec2);

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
	bool RigthCheck; //오른쪽 벡터에 장애물이 있는지
	bool LeftCheck; // 왼쪽 벡터에 장애물이 있는지
	bool IsMoving;

	FTimerHandle  Delay;
	FTimerHandle InitTime;

	bool IsLookAround;
	bool LeftEnd;
	float LeftAngle;
	float RightAngle;
	int LookCount;

	void LookAround();
	void LookAroundStart();

	virtual void Shooting(float tick) override;
	FVector Prediction();

	AIState CurState;

	void Update();

	void MoveCover();//엄페물로 이동
	void NextCover();//엄페물 선택
	void NextCover(FVector Destination);
	void CheckSafe();//엄페물 도착여부
	void CheckSafe(FVector Destination);

	bool IsLookTarget;

	void MoveToLocation(FVector Location);

	void Hide(AActor * Attacker);
	bool Hiding;



	bool MoveEnd;

	void SetRandomLocation(); //아무것도 판단할 근거가 없을때 이동 경로 지정

	void Attacked(AActor * Attacker);  //공격받았을때 판단함수
	void FindPlayer(); //캐릭터를 발견했을때 판단


	void InitTargetPlayer();

};

