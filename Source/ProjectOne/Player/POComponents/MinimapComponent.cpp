// Fill out your copyright notice in the Description page of Project Settings.

#include "MinimapComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Components/SceneCaptureComponent2D.h"

// Sets default values for this component's properties
UMinimapComponent::UMinimapComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	//¹Ì´Ï¸Ê
	MinimapArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MinimapArm"));
	MinimapArm->TargetArmLength = 300.0f;

	MinimapCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MinimapCamera"));

	ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> TargetAsset(TEXT("TextureRenderTarget2D'/Game/Materail/MiniMapRenderTarget.MiniMapRenderTarget'"));
	if (TargetAsset.Succeeded()) {
		MinimapTarget = TargetAsset.Object;
	}
	MinimapCamera->TextureTarget = MinimapTarget;
	
	ConstructorHelpers::FObjectFinder<UPaperSprite> PlayerSpriteAsset(TEXT("PaperSprite'/Game/UISprite/PlayerPos_Sprite.PlayerPos_Sprite'"));
	if (PlayerSpriteAsset.Succeeded()) {
		PlayerSprite = PlayerSpriteAsset.Object;
	}
	MinimapPlayerSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MinimapPlayerSprite"));
	MinimapPlayerSprite->SetSprite(PlayerSprite);
	MinimapPlayerSprite->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	MinimapPlayerSprite->bOwnerNoSee = true;
	// ...
}

void UMinimapComponent::InitAttachment(USceneComponent * rootComponent)
{
	MinimapArm->SetupAttachment(rootComponent);
	MinimapCamera->SetupAttachment(rootComponent);
	MinimapPlayerSprite->SetupAttachment(rootComponent);
}