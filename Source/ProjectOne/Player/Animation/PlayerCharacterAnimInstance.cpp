// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacterAnimInstance.h"

UPlayerCharacterAnimInstance::UPlayerCharacterAnimInstance() {
	Forward = 0.0f;
	Right = 0.0f;
}


void UPlayerCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();

	if (::IsValid(Pawn))
	{

		

		//	GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Red, FString::SanitizeFloat(PawnForwardSpeed) + FString::SanitizeFloat(PawnRightSpeed));
	}
}