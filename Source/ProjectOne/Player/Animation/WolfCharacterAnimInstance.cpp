// Fill out your copyright notice in the Description page of Project Settings.

#include "WolfCharacterAnimInstance.h"

void UWolfCharacterAnimInstance::SetRollMontage() {
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ROLL_MONTAGE(TEXT("AnimMontage'/Game/Animations/Exper/SK_Wolf1_Roll_Front_Montage.SK_Wolf1_Roll_Front_Montage'"));
	if (ROLL_MONTAGE.Succeeded())
		RollMontage = ROLL_MONTAGE.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SecROLL_MONTAGE(TEXT("AnimMontage'/Game/Animations/Wolf2/SK_Wolf2_Roll_Front_Montage.SK_Wolf2_Roll_Front_Montage'"));
	if (SecROLL_MONTAGE.Succeeded())
		SecondRollMontage = SecROLL_MONTAGE.Object;
}

UWolfCharacterAnimInstance::UWolfCharacterAnimInstance() {
	SetRollMontage();
}

void UWolfCharacterAnimInstance::Evolution() {
	RollMontage = SecondRollMontage;
}