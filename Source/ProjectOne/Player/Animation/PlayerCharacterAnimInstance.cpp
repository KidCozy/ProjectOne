// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacterAnimInstance.h"
#include "GameFramework/Character.h"

void UPlayerCharacterAnimInstance::SetRollMontage() {
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ROLL_MONTAGE(TEXT("AnimMontage'/Game/Animations/AnimStarterPack/PlayerRollForward_Root_Montage.PlayerRollForward_Root_Montage'"));
	if (ROLL_MONTAGE.Succeeded())
		RollMontage = ROLL_MONTAGE.Object;
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SecROLL_MONTAGE(TEXT("AnimMontage'/Game/Animations/AnimStarterPack/PlayerRollForward_Root_Montage.PlayerRollForward_Root_Montage'"));
	if (SecROLL_MONTAGE.Succeeded())
		SecondRollMontage = SecROLL_MONTAGE.Object;

}

void UPlayerCharacterAnimInstance::Evolution() {

}

UPlayerCharacterAnimInstance::UPlayerCharacterAnimInstance() {
	Forward = 0.0f;
	Right = 0.0f;
	isRoll = false;
	SetRollMontage();
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