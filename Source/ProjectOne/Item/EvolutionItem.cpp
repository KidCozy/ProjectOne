// Fill out your copyright notice in the Description page of Project Settings.

#include "EvolutionItem.h"
#include "Player/ProjectOneCharacter.h"
#include "Player/POComponents/PlayerStatComponent.h"

AEvolutionItem::AEvolutionItem() 
{
	eItem = E_Item::E_EVOLUTION;
}

void AEvolutionItem::Use()
{
	if (ItemOwner->CurLevel > 1)
	{
		ItemOwner->Evolution();
	}

	else
	{
		ItemOwner->CharacterStat->CurHP = ItemOwner->CharacterStat->GetMaxHP();
	}
}
