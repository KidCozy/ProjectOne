// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacterAnimInstance.h"
#include "GameFramework/Character.h"

void UPlayerCharacterAnimInstance::SetMontage() {


}

void UPlayerCharacterAnimInstance::Evolution() {
	F_RollMontage = SecondRollMontage;
}

UPlayerCharacterAnimInstance::UPlayerCharacterAnimInstance() {
	Forward = 0.0f;
	Right = 0.0f;
	isRoll = false;
	SetMontage();
}

void UPlayerCharacterAnimInstance::AnimNotify_RollEnd()
{
	isRoll = false;
}

void UPlayerCharacterAnimInstance::AnimNotify_JumpEnd()
{
	isInAir = false;
}

void UPlayerCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();

	if (::IsValid(Pawn))
	{
		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
			isInAir = Character->GetMovementComponent()->IsFalling();
	}
}