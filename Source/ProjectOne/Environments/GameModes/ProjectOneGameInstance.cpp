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
	FString CharacterDataPath = TEXT("DataTable'/Game/Data/Character.Character'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CHARACTER(*CharacterDataPath);
	ABCHECK(DT_CHARACTER.Succeeded());
	CharacterTable = DT_CHARACTER.Object;
	ABCHECK(CharacterTable->GetRowMap().Num() > 0);

	FString WeaponeDataPath = TEXT("DataTable'/Game/Data/Weapon.Weapon'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_WEAPONE(*WeaponeDataPath);
	ABCHECK(DT_WEAPONE.Succeeded());
	WeaponeTable = DT_WEAPONE.Object;
	ABCHECK(WeaponeTable->GetRowMap().Num() > 0);
}

FPOCharcacterData * UProjectOneGameInstance::GetCharcterData(int32 ID)
{
	return CharacterTable->FindRow<FPOCharcacterData>(*FString::FromInt(ID), TEXT(""));
}

FPOWeaponeData * UProjectOneGameInstance::GetWeaponData(int32 ID)
{
	return WeaponeTable->FindRow<FPOWeaponeData>(*FString::FromInt(ID), TEXT(""));
}


void UProjectOneGameInstance::Init() {
	Super::Init();
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
//
//E_PlayerSelect UProjectOneGameInstance::GetPlayerType()
//{
//	return PlayerType;
//}
//
//void UProjectOneGameInstance::SetPlayerType(E_PlayerSelect playerType)
//{
//	PlayerType = playerType;
//}
