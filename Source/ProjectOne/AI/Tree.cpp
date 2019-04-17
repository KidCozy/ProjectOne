// Fill out your copyright notice in the Description page of Project Settings.

#include "Tree.h"

void ATree::BeginPlay()
{
	Super::BeginPlay();



	SafePos.Add(FVector(GetActorLocation().X, GetActorLocation().Y + 120.0f, 98.0f));
	SafePos.Add(FVector(GetActorLocation().X+120.0f, GetActorLocation().Y + 120.0f, 98.0f));
	SafePos.Add(FVector(GetActorLocation().X - 120.0f, GetActorLocation().Y + 120.0f, 98.0f));
	SafePos.Add(FVector(GetActorLocation().X, GetActorLocation().Y - 120.0f, 98.0f));
	SafePos.Add(FVector(GetActorLocation().X+120.0f, GetActorLocation().Y - 120.0f, 98.0f));
	SafePos.Add(FVector(GetActorLocation().X - 120.0f, GetActorLocation().Y - 120.0f, 98.0f));
	SafePos.Add(FVector(GetActorLocation().X + 120.0f, GetActorLocation().Y, 98.0f));
	SafePos.Add(FVector(GetActorLocation().X - 120.0f, GetActorLocation().Y, 98.0f));


}

ATree::ATree()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = Mesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PJ_Mesh(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	if (PJ_Mesh.Succeeded())
	{
		Mesh->SetStaticMesh(PJ_Mesh.Object);
	}

	
}