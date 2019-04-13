// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectOneAIController.h"
#include "DrawDebugHelpers.h"




AProjectOneAIController::AProjectOneAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	bSetControlRotationFromPawnOrientation = 0;
}

void AProjectOneAIController::Tick(float delta)
{
	Super::Tick(delta);

	//FVector End;

	//End = GetPawn()->GetActorForwardVector() * 255.0f;
	//End = GetPawn()->GetActorLocation() + End;

	//DrawDebugLine(GetWorld(), GetPawn()->GetActorLocation(), End, FColor::Green, false, 1, 0, 1);

	//
	//GetWorld()->GetTimerManager().SetTimer(Delay, this, &AProjectOneAIController::Update, 0.5f, false);
	//UE_LOG(LogTemp, Warning, TEXT("%f,%f,%f"), End.X, End.Y, End.Z);
	//MoveToLocation(End, -1.0f, true, true, true, true, 0, true);
	//MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn());
	//ABLOG_S(Warning);
}

void AProjectOneAIController::BeginPlay()
{
	Super::BeginPlay();
	


	//GetWorld()->GetTimerManager().SetTimer(Delay, this, &AProjectOneAIController::Update, 0.5f, false);
}

void AProjectOneAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

}


void AProjectOneAIController::Update()
{
	FHitResult OutHit;

	FVector End;

	End = GetPawn()->GetActorForwardVector() * 500.0f;
	End = GetPawn()->GetActorLocation() + End;

	DrawDebugLine(GetWorld(), GetPawn()->GetActorLocation(), End, FColor::Green, false, 1, 0, 1);

	ABLOG_S(Warning);
	ABLOG(Warning, TEXT("%f,%f,%f"), End.X, End.Y, End.Z);
	MoveToLocation(End, -1.0f, true);
	GetWorld()->GetTimerManager().SetTimer(Delay, this, &AProjectOneAIController::Update, 0.5f, false);

	FTimerHandle  Delay;

}