// Fill out your copyright notice in the Description page of Project Settings.

#include "HealItem.h"
#include "ProjectOneClasses.h"
#include "Player/POComponents/PlayerStatComponent.h"
#include "Player/ProjectOneCharacter.h"
#include "AI/AICharacter.h"

AHealItem::AHealItem() 
{
	eItem = E_Item::E_HEAL_50;
	HealAmount = 50.0f;
	ConstructorHelpers::FObjectFinder<UParticleSystem> P_HEAL(TEXT("ParticleSystem'/Game/rgyEffect01/Particle/P06/P06_Heal1.P06_Heal1'"));
	if(P_HEAL.Succeeded())
		UseEffect = P_HEAL.Object;

}

void AHealItem::SetHealItem(E_Item item)
{
	eItem = item;
	switch (eItem) {
	case E_Item::E_HEAL_50:
		HealAmount = 50.0f;
		break;
	case E_Item::E_HEAL_100:
		HealAmount = 100.0f;
		break;
	case E_Item::E_HEAL_150:
		HealAmount = 150.0f;
		break;
	}
}

void AHealItem::Use() 
{
	ItemOwner->HealEffect->SetTemplate(UseEffect);
	ItemOwner->HealEffect->SetActive(true);
	if (!ItemOwner->IsA(AAICharacter::StaticClass())) {
		ItemOwner->AteHealItem = true;
	}
	if (ItemOwner->CharacterStat->CurHP + HealAmount >= ItemOwner->CharacterStat->GetMaxHP())
		ItemOwner->CharacterStat->CurHP = ItemOwner->CharacterStat->GetMaxHP();
	else
		ItemOwner->CharacterStat->CurHP += HealAmount;
}
