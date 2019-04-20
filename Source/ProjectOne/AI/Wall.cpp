// Fill out your copyright notice in the Description page of Project Settings.

#include "Wall.h"

void AWall::BeginPlay()
{


	SafePos.Add(FVector(GetActorLocation().X -130.0f, GetActorLocation().Y + 150.0f, 251.0f));
	SafePos.Add(FVector(GetActorLocation().X - 130.0f, GetActorLocation().Y, 251.0f));
	SafePos.Add(FVector(GetActorLocation().X - 130.0f, GetActorLocation().Y - 150.0f, 251.0f));

	SafePos.Add(FVector(GetActorLocation().X + 130.0f, GetActorLocation().Y + 150.0f, 251.0f));
	SafePos.Add(FVector(GetActorLocation().X + 130.0f, GetActorLocation().Y, 251.0f));
	SafePos.Add(FVector(GetActorLocation().X + 130.0f, GetActorLocation().Y - 150.0f, 251.0f));


	SafePos.Add(FVector(GetActorLocation().X, GetActorLocation().Y + 270.0f, 251.0f));
	SafePos.Add(FVector(GetActorLocation().X, GetActorLocation().Y - 270.0f, 251.0f));


	
}

AWall::AWall()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = Mesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PJ_Mesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (PJ_Mesh.Succeeded())
	{
		Mesh->SetStaticMesh(PJ_Mesh.Object);
	}

	SetActorScale3D(FVector(1.0f, 4.0f, 3.0f));
}
