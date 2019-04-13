// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "Components/SceneComponent.h"
#include "MinimapComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTONE_API UMinimapComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMinimapComponent();

	void InitAttachment(USceneComponent* rootComponent);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Minimap)
	class USpringArmComponent* MinimapArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Minimap)
	class USceneCaptureComponent2D*  MinimapCamera;
	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Minimap)
	class UPaperSpriteComponent* MinimapPlayerSprite;

protected:
	UPROPERTY(VisibleAnywhere, Category = Minimap)
	class UTextureRenderTarget2D* MinimapTarget;

	UPROPERTY(VisibleAnywhere, Category = Minimap)
	class UPaperSprite* PlayerSprite;
};
