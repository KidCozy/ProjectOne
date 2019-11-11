// Fill out your copyright notice in the Description page of Project Settings.

#include "POPlayerAkComponent.h"
#include "AkAudioEvent.h"
#include "AkAudioDevice.h"


UPOPlayerAkComponent::UPOPlayerAkComponent() {
	ConstructorHelpers::FObjectFinder<UAkAudioEvent> PISTOLSOUND(TEXT("AkAudioEvent'/Game/Sound/Character/Pistol_Shot.Pistol_Shot'"));
	if (PISTOLSOUND.Succeeded()) {
		PistolSound = PISTOLSOUND.Object;
	}
	ConstructorHelpers::FObjectFinder<UAkAudioEvent> HITSOUND(TEXT("AkAudioEvent'/Game/Sound/Character/Bullet_Hit.Bullet_Hit'"));
	if (HITSOUND.Succeeded()) {
		BulletCrashSound = HITSOUND.Object;
	}
}

void UPOPlayerAkComponent::PlayPistolShotSound()
{
	FAkAudioDevice::Get()->PostEvent(PistolSound, GetOwner());
}

void UPOPlayerAkComponent::PlayBulletCrashSound()
{
	FAkAudioDevice::Get()->PostEvent(BulletCrashSound, GetOwner());
}