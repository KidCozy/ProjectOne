// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "Components/SceneComponent.h"
#include "InventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTONE_API UInventoryComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();
	//이미지용 Enum
	UPROPERTY(VisibleAnywhere)
	TArray<E_Item> eItems;
	
	UPROPERTY(VisibleAnywhere)
	TArray<class ASuperItem*> Items;

	uint8 InventorySize = 3;

public:
	UFUNCTION(BlueprintCallable)
	E_Item GetItem(uint8 Index);

	void SetItem(class ASuperItem* NewItem);

	void UseItem(uint8 Index);
};
