// Fill out your copyright notice in the Description page of Project Settings.

#include "ThrowableItem.h"

// Sets default values
AThrowableItem::AThrowableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

void AThrowableItem::Aim()
{

}

void AThrowableItem::Launch()
{
	
	auto CameraForward = ItemOwner->FollowCamera->GetForwardVector();

	Mesh->AddForce(CameraForward * LaunchVelocity);
}