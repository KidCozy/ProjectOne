// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectOneGameInstance.h"

UProjectOneGameInstance::UProjectOneGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UCameraShake> CSHAKE_BY_PISTOL(TEXT("Blueprint'/Game/Temp/PistolShotShake.PistolShotShake_C'"));
	//	static ConstructorHelpers::FClassFinder<UCameraShake> CSHAKE_BY_BOSS_SMASH(TEXT("dsd"));



	if (CSHAKE_BY_PISTOL.Succeeded())
		CShakePistol = CSHAKE_BY_PISTOL.Class;
	//	static ConstructorHelpers::FClassFinder<UCameraShake> CSHAKE_BY_BOSS_DIVE(TEXT("DASD"));
	//	static ConstructorHelpers::FClassFinder<UCameraShake> CSHAKE_BY_PLAYER_ATTACK(TEXT("DASDS"));

}


void UProjectOneGameInstance::Init() {





}

void UProjectOneGameInstance::HitShake(TSubclassOf<UCameraShake> CShake, float Scalar) {
	FTimerHandle time_;
	if (CShake != nullptr)
	{
		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(CShake, Scalar);
	}



	//auto Character = Cast<AProjectOneCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	//Character->Camera->PostProcessSettings.SceneFringeIntensity = 5.0f;
	//Character->GetWorldTimerManager().SetTimer(time_, Character, &AProjectOneCharacter::HitPostProcess, 0.5f, false);


}