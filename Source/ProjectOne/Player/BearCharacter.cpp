// Fill out your copyright notice in the Description page of Project Settings.

#include "BearCharacter.h"
#include "Weapons/Pistol.h"

ABearCharacter::ABearCharacter() {
}

void ABearCharacter::SetResources()
{
	static ConstructorHelpers::FClassFinder<UCameraShake> CSHAKE_FIRE(TEXT("Blueprint'/Game/ScreenFX/CShake_Fire.CShake_Fire_C'"));
	if (CSHAKE_FIRE.Succeeded())
		CShakeList.Add(CSHAKE_FIRE.Class);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MANEQUIN(TEXT("SkeletalMesh'/Game/Animations/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (SK_MANEQUIN.Succeeded())
		GetMesh()->SetSkeletalMesh(SK_MANEQUIN.Object);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FClassFinder<UAnimInstance> TEMP_ANIM(TEXT("AnimBlueprint'/Game/Animations/AnimationBlueprint/PlayerCharacter_AnimBP.PlayerCharacter_AnimBP_C'"));
	if (TEMP_ANIM.Succeeded())
		GetMesh()->SetAnimInstanceClass(TEMP_ANIM.Class);
	UE_LOG(LogTemp, Warning, TEXT("BearReSource"));
}

void ABearCharacter::SetInitWeapone()
{
	Weapone->InitWeapone(1, 2.0f, 1.0f, 1.0f, 3.0f, 100.0f);
}

void ABearCharacter::Shooting(float tick)
{
}
