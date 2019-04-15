// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAkComponent.h"
#include "AkAudioEvent.h"

UPlayerAkComponent::UPlayerAkComponent()
{
	////audio
	static ConstructorHelpers::FObjectFinder<UAkAudioEvent> SHOTEVENT(TEXT("AkAudioEvent'/Game/Sounds/Pistol.Pistol'"));
	if (SHOTEVENT.Succeeded()) {
		Pistol = SHOTEVENT.Object;
	}
	AkAudioEvent = Pistol;
}

void UPlayerAkComponent::PlayShotSound() {

	FAkAudioDevice* Device = FAkAudioDevice::Get();
	Device->PostEvent(AkAudioEvent, Player);
}

void UPlayerAkComponent::SetPlayer(AProjectOneCharacter * player)
{
	Player = player;
}
