// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacterAnimInstance.h"
#include "Player/ProjectOneCharacter.h"
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

void UPlayerCharacterAnimInstance::RollBackMontage()
{
	if (isShooting)
		Montage_JumpToSection("Default");
}

void UPlayerCharacterAnimInstance::AnimNotify_RollEnd()
{
	isRoll = false;
}

void UPlayerCharacterAnimInstance::AnimNotify_JumpEnd()
{
	isInAir = false;
}

void UPlayerCharacterAnimInstance::AnimNotify_ReloadEnd()
{
	auto Pawn = TryGetPawnOwner();

	if (::IsValid(Pawn))
	{
		auto Character = Cast<AProjectOneCharacter>(Pawn);
		if (Character)
			Character->ReLoad();
	}
}

void UPlayerCharacterAnimInstance::AnimNotify_Shootable()
{
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		auto Character = Cast<AProjectOneCharacter>(Pawn);
		if (Character->ShootInput)
			isShooting = true;
		else
			isShooting = false;
	}
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
