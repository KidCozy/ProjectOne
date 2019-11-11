// Fill out your copyright notice in the Description page of Project Settings.

#include "SuckSangItem.h"
#include "ProjectOne/Player/ProjectOneCharacter.h"

ASuckSangItem::ASuckSangItem() {
	ConstructorHelpers::FObjectFinder<UMaterialInstance> M_SUCKSANG(TEXT("MaterialInstanceConstant'/Game/Materail/M_Stone_Inst.M_Stone_Inst'"));
	if(M_SUCKSANG.Succeeded())
		SuckSangMaterial = M_SUCKSANG.Object;

	eItem = E_Item::E_SUCKSANG;

	DurationTime = 5;
}

void ASuckSangItem::Use() {
	ItemOwner->isPause = true;
	for (int i = 0; i < 3; i++)
		OwnerMaterials.Add(ItemOwner->GetMesh()->GetMaterial(i));
	for (int i = 0; i < 3; i++)
		ItemOwner->GetMesh()->SetMaterial(i, SuckSangMaterial);

	ItemOwner->GetMesh()->GlobalAnimRateScale = 0.0f;
	ItemOwner->GetCharacterMovement()->bUseControllerDesiredRotation = false;
	ItemOwner->GetCharacterMovement()->bOrientRotationToMovement = true;
	GetWorld()->GetTimerManager().SetTimer(DurationTimer, this, &ASuckSangItem::Duration, 1.0f, true);
}

void ASuckSangItem::DurationEnd()
{
	ItemOwner->isPause = false;
	for (int i = 0; i < 3; i++)
		ItemOwner->GetMesh()->SetMaterial(i, OwnerMaterials[i]);

	ItemOwner->GetMesh()->GlobalAnimRateScale = 1.0f;
}

