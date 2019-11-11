// Fill out your copyright notice in the Description page of Project Settings.

#include "LauncherCharacter.h"
#include "POComponents/PlayerStatComponent.h"

ALauncherCharacter::ALauncherCharacter()
{
	SetResources();
}


void ALauncherCharacter::SetResources()
{
	static ConstructorHelpers::FClassFinder<UCameraShake> CSHAKE_FIRE(TEXT("Blueprint'/Game/ScreenFX/CShake_Fire.CShake_Fire_C'"));
	if (CSHAKE_FIRE.Succeeded())
		CShakeList.Add(CSHAKE_FIRE.Class);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MANEQUIN(TEXT("SkeletalMesh'/Game/Animations/Wolf1/SK_Wolf1_Idle.SK_Wolf1_Idle'"));
	if (SK_MANEQUIN.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SK_MANEQUIN.Object);
		FirstMesh = SK_MANEQUIN.Object;
	}

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -42.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FClassFinder<UAnimInstance> TEMP_ANIM(TEXT("AnimBlueprint'/Game/Animations/Wolf1/BP_Wolf1.BP_Wolf1_C'"));
	if (TEMP_ANIM.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(TEMP_ANIM.Class);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Sec(TEXT("SkeletalMesh'/Game/Animations/Wolf2/Launcher/SK_Wolf2_Attack_LC.SK_Wolf2_Attack_LC'"));
	if (SK_Sec.Succeeded()) {
		SecondSkMesh = SK_Sec.Object;
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_THIRD(TEXT("SkeletalMesh'/Game/Animations/Wolf3/Launcher/SK_Wolf3_Attack_LC.SK_Wolf3_Attack_LC'"));
	if (SK_THIRD.Succeeded()) {
		ThirdMesh = SK_THIRD.Object;
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_Sec(TEXT("AnimBlueprint'/Game/Animations/Wolf2/Launcher/BP_Wolf2_Launcher.BP_Wolf2_Launcher_C'"));
	if (ANIM_Sec.Succeeded()) {
		SecondAnimIns = ANIM_Sec.Class;
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_THIRD(TEXT("AnimBlueprint'/Game/Animations/Wolf3/Launcher/BP_Wolf3_Launcher.BP_Wolf3_Launcher_C'"));
	if (ANIM_THIRD.Succeeded()) {
		ThirdAnimIns = ANIM_THIRD.Class;
	}

	EvolEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EVOLEFFECT"));
	EvolEffect->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_EVOL(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_gaither.P_ky_gaither'"));
	if (P_EVOL.Succeeded())
	{
		EvolEffect->SetTemplate(P_EVOL.Object);
		EvolEffect->bAutoActivate = false;
	}

	GetMesh()->SetRelativeScale3D(FVector(0.7f, 0.7f, 0.7f));
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -45.0f));
	CameraBoom->SocketOffset = FVector(240.0f, 40.0f, 50.0f);
	GetMesh()->SetRelativeScale3D(FVector(0.7f));	
	PlayerType = E_PlayerSelect::E_LAUNCHER;
	CharacterStat->SetCharacterID((int)PlayerType);
	
}
