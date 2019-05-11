// Fill out your copyright notice in the Description page of Project Settings.

#include "WolfCharacterAnimInstance.h"

void UWolfCharacterAnimInstance::SetMontage() {
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ROLL_MONTAGE1(TEXT("AnimMontage'/Game/Animations/Exper/Roll/SK_Wolf1_Roll_Front_Montage.SK_Wolf1_Roll_Front_Montage'"));
	if (ROLL_MONTAGE1.Succeeded())
		F_RollMontage = ROLL_MONTAGE1.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ROLL_MONTAGE2(TEXT("AnimMontage'/Game/Animations/Exper/Roll/SK_Wolf1_Roll_Back_Montage.SK_Wolf1_Roll_Back_Montage'"));
	if (ROLL_MONTAGE2.Succeeded())
		B_RollMontage = ROLL_MONTAGE2.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ROLL_MONTAGE3(TEXT("AnimMontage'/Game/Animations/Exper/Roll/SK_Wolf1_Roll_Left_Montage.SK_Wolf1_Roll_Left_Montage'"));
	if (ROLL_MONTAGE3.Succeeded())
		L_RollMontage = ROLL_MONTAGE3.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ROLL_MONTAGE4(TEXT("AnimMontage'/Game/Animations/Exper/Roll/SK_Wolf1_Roll_Right_Montage.SK_Wolf1_Roll_Right_Montage'"));
	if (ROLL_MONTAGE4.Succeeded())
		R_RollMontage = ROLL_MONTAGE4.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SecROLL_MONTAGE(TEXT("AnimMontage'/Game/Animations/Wolf2/SK_Wolf2_Roll_Front_Montage.SK_Wolf2_Roll_Front_Montage'"));
	if (SecROLL_MONTAGE.Succeeded())
		SecondRollMontage = SecROLL_MONTAGE.Object;
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SHOTMONTAGE(TEXT("AnimMontage'/Game/Animations/Exper/SK_Wolf1_Attack_Montage.SK_Wolf1_Attack_Montage'"));
	if (SHOTMONTAGE.Succeeded())
		ShotMontage = SHOTMONTAGE.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SecATTACK_MONTAGE(TEXT("AnimMontage'/Game/Animations/Wolf2Build/Attack/SK_Wolf2_Attack_Montage.SK_Wolf2_Attack_Montage'"));
	if (SecATTACK_MONTAGE.Succeeded())
		SecondShotMontage = SecATTACK_MONTAGE.Object;

}

UWolfCharacterAnimInstance::UWolfCharacterAnimInstance() {
	SetMontage();
}

void UWolfCharacterAnimInstance::Evolution() {
	//F_RollMontage = SecondRollMontage;
	//B_RollMontage = SecondRollMontage;
	//L_RollMontage = SecondRollMontage;
	//R_RollMontage = SecondRollMontage;
	//ShotMontage = SecondShotMontage;
}