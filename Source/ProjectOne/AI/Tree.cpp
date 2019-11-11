// Fill out your copyright notice in the Description page of Project Settings.

#include "Tree.h"

void ATree::BeginPlay()
{




	SafePos.Add(FVector(GetActorLocation().X, GetActorLocation().Y + 120.0f, 251.0f));
	SafePos.Add(FVector(GetActorLocation().X+120.0f, GetActorLocation().Y + 120.0f, 251.0f));
	SafePos.Add(FVector(GetActorLocation().X - 120.0f, GetActorLocation().Y + 120.0f, 251.0f));
	SafePos.Add(FVector(GetActorLocation().X, GetActorLocation().Y - 150.0f, 251.0f));
	SafePos.Add(FVector(GetActorLocation().X+120.0f, GetActorLocation().Y - 150.0f, 251.0f));
	SafePos.Add(FVector(GetActorLocation().X - 120.0f, GetActorLocation().Y - 120.0f, 251.0f));
	SafePos.Add(FVector(GetActorLocation().X + 160.0f, GetActorLocation().Y, 251.0f));
	SafePos.Add(FVector(GetActorLocation().X - 120.0f, GetActorLocation().Y, 251.0f));


}


ATree::ATree()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Pivot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PIVOT"));

	RootComponent = Pivot;

	Mesh->SetupAttachment(RootComponent);

	RootComponent->SetMobility(EComponentMobility::Static);
	Mesh->SetMobility(EComponentMobility::Static);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PJ_Mesh(TEXT("StaticMesh'/Game/BuildMap/Rodents/Environment/Trees/SimpleTree/S_BuildingSetA_Tree_02.S_BuildingSetA_Tree_02'"));
	if (PJ_Mesh.Succeeded())
	{
		Mesh->SetStaticMesh(PJ_Mesh.Object);
	}


	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MAT_Trunk(TEXT("MaterialInstanceConstant'/Game/BuildMap/Rodents/Environment/Trees/SimpleTree/M_TreeTrunk01_Inst.M_TreeTrunk01_Inst'"));
	if (MAT_Trunk.Succeeded())
	{
		Mesh->SetMaterial(0, MAT_Trunk.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MAT_Branches(TEXT("MaterialInstanceConstant'/Game/BuildMap/Rodents/Environment/Trees/SimpleTree/M_Tree_Branches_Inst.M_Tree_Branches_Inst'"));
	if (MAT_Branches.Succeeded())
	{
		Mesh->SetMaterial(1, MAT_Branches.Object);
	}



	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -270.0f));
	
}