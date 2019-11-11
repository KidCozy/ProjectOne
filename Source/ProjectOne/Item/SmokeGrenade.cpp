// Fill out your copyright notice in the Description page of Project Settings.

#include "SmokeGrenade.h"

void ASmokeGrenade::InitAssets()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SMOKE_MESH(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (SMOKE_MESH.Succeeded())
		Mesh->SetStaticMesh(SMOKE_MESH.Object);

	//static ConstructorHelpers::FObjectFinder<UParticleSystem> SMOKE_PARTICLE()
}

void ASmokeGrenade::Use()
{


}
