// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "ProjectOne/Item/SuperItem.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	for (int i = 0; i < InventorySize; i++)
	{
		eItems.Add(E_Item::E_NONE);
		Items.Add(nullptr);
	}
}

E_Item UInventoryComponent::GetItem(uint8 Index)
{
	return eItems[Index];
}

void UInventoryComponent::SetItem(ASuperItem* NewItem)
{
	for (int i = 0 ; i < InventorySize; i++) 
	{
		if (eItems[i] == E_Item::E_NONE) 
		{
			eItems[i] = NewItem->eItem;
			Items[i] = NewItem;
			break;
		}
	}
}

void UInventoryComponent::UseItem(uint8 Index)
{
	if (!Items[Index])
		return;
	else 
	{
		Items[Index]->Use();
		Items[Index] = nullptr;
		eItems[Index] = E_Item::E_NONE;
	}
}

