// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

APlayerCharacter::APlayerCharacter() {
	static ConstructorHelpers::FClassFinder<UAnimInstance> CHARACTER_ANIM(TEXT("AnimBlueprint'/Game/Animations/AnimationBlueprint/PlayerCharacter_AnimBP.PlayerCharacter_AnimBP_C'"));
	
	if (CHARACTER_ANIM.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(CHARACTER_ANIM.Class);
	}

}