// Fill out your copyright notice in the Description page of Project Settings.

#include "SpeedBuffItem.h"
#include "ProjectOne/Player/ProjectOneCharacter.h"
ASpeedBuffItem::ASpeedBuffItem() {
	eItem = E_Item::E_SPEED_BUFF;
}

void ASpeedBuffItem::Use()
{
	ItemOwner->GetCharacterMovement()->MaxWalkSpeed = 700.0f;
	DurationTime = 5.0f;
	GetWorld()->GetTimerManager().SetTimer(DurationTimer, this, &ASpeedBuffItem::Duration, 1.0f, true);
}

void ASpeedBuffItem::DurationEnd()
{

	ItemOwner->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}
