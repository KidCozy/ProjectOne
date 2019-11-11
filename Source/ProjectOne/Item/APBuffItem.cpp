// Fill out your copyright notice in the Description page of Project Settings.

#include "APBuffItem.h"
#include "ProjectOne/Player/ProjectOneCharacter.h"
AAPBuffItem::AAPBuffItem() {
	eItem = E_Item::E_AP_BUFF;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_Shield(TEXT("ParticleSystem'/Game/rgyEffect01/Particle/P07/P07_Shield.P07_Shield'"));
	if (P_Shield.Succeeded())
	{
		UseEffect = P_Shield.Object;
	}
}

void AAPBuffItem::Use() {
	ItemOwner->SheildEffect->SetTemplate(UseEffect);
	ItemOwner->SheildEffect->SetActive(true);
}