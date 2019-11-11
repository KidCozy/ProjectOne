// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerStatComponent.h"
#include "Environments/GameModes/ProjectOneGameInstance.h"
// Sets default values for this component's properties
UPlayerStatComponent::UPlayerStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	CharID = 1;
	WeaponeID = 1;
	// ...
}



// Called when the game starts
void UPlayerStatComponent::BeginPlay()
{
	Super::BeginPlay();
	CurHP = 200;

	// ...
	
}

void UPlayerStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetCharacterID(CharID);
	SetWeaponeID(WeaponeID);
}


void UPlayerStatComponent::SetCharacterID(int32 id)
{
	auto GameInstace = Cast<UProjectOneGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (nullptr != CurCharStatData) {
		CharID = id;
	}

	ABCHECK(nullptr != GameInstace);
	CurCharStatData = GameInstace->GetCharcterData(CharID);
}

void UPlayerStatComponent::SetWeaponeID(int32 id)
{
	auto GameInstace = Cast<UProjectOneGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (nullptr != CurWeaponeStatData) {
		WeaponeID = id;
	}

	ABCHECK(nullptr != GameInstace);
	CurWeaponeStatData = GameInstace->GetWeaponData(WeaponeID);
}

FPOCharcacterData * UPlayerStatComponent::GetCharacterStatData()
{
	return CurCharStatData;
}

FPOWeaponeData * UPlayerStatComponent::GetWeaphoneStatData()
{
	return CurWeaponeStatData;
}

int UPlayerStatComponent::GetMaxHP()
{
	return GetCharacterStatData()->HP;
}
