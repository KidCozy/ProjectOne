// Fill out your copyright notice in the Description page of Project Settings.

#include "WolfCharacter.h"
#include "POComponents/PlayerAkComponent.h"
#include "PlayerStatComponent.h"
#include "Weapons/Pistol.h" 
AWolfCharacter::AWolfCharacter(){
	SetResources();
}

void AWolfCharacter::SetResources() {
	static ConstructorHelpers::FClassFinder<UCameraShake> CSHAKE_FIRE(TEXT("Blueprint'/Game/ScreenFX/CShake_Fire.CShake_Fire_C'"));
	if (CSHAKE_FIRE.Succeeded())
		CShakeList.Add(CSHAKE_FIRE.Class);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MANEQUIN(TEXT("SkeletalMesh'/Game/Animations/Exper/SK_Wolf1_Idle.SK_Wolf1_Idle_dog0F'"));
	if (SK_MANEQUIN.Succeeded())
		GetMesh()->SetSkeletalMesh(SK_MANEQUIN.Object);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -32.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FClassFinder<UAnimInstance> TEMP_ANIM(TEXT("AnimBlueprint'/Game/Animations/Exper/Wolf1_AnimBP.Wolf1_AnimBP_C'"));
	if (TEMP_ANIM.Succeeded())
		GetMesh()->SetAnimInstanceClass(TEMP_ANIM.Class);

	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Sec(TEXT("SkeletalMesh'/Game/Animations/Wolf2/SK_Wolf2_Idle.SK_Wolf2_Idle_Box001'"));
	if (SK_Sec.Succeeded())
		SecondSkMesh = SK_Sec.Object;

	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_Sec(TEXT("AnimBlueprint'/Game/Animations/Wolf2/BP_Wolf2Anim.BP_Wolf2Anim_C'"));
	if (ANIM_Sec.Succeeded()) {
		SecondAnimIns = ANIM_Sec.Class;
	}
	
}

void AWolfCharacter::Evolution() {
	GetMesh()->SetSkeletalMesh(SecondSkMesh);
	GetMesh()->SetAnimInstanceClass(SecondAnimIns);
	APAnim = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	GetCapsuleComponent()->InitCapsuleSize(20.0f, 70.0f);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -70.0f));

	//8,0,2
	//65,-10,25
	Weapone->SetActorRelativeLocation(FVector(65.0f, -10.0f, 25.0f));
	APAnim->Evolution();
}