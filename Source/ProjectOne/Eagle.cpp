// Fill out your copyright notice in the Description page of Project Settings.

#include "Eagle.h"

// Sets default values
AEagle::AEagle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = Mesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PJ_Mesh(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	if (PJ_Mesh.Succeeded())
	{
		Mesh->SetStaticMesh(PJ_Mesh.Object);
	}


	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MAT_Trunk(TEXT("MaterialInstanceConstant'/Game/Temp/M_Eagle_Inst.M_Eagle_Inst'"));
	if (MAT_Trunk.Succeeded())
	{
		Mesh->SetMaterial(0, MAT_Trunk.Object);
	}

	bCheck = false;

}

// Called when the game starts or when spawned
void AEagle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEagle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + GetActorForwardVector() * Speed);

	if (bTurn) {
		if (GetActorRotation().Yaw <= Angle && !bCheck)
			SetActorRotation(GetActorRotation() + FRotator(0, TurnSpeed, 0));

		if (GetActorRotation().Yaw >= -Angle && bCheck)
			SetActorRotation(GetActorRotation() - FRotator(0, TurnSpeed, 0));

		if (GetActorRotation().Yaw >= Angle && !bCheck)
		{
			bCheck = true;
		}

		if (GetActorRotation().Yaw <= -Angle && bCheck)
		{
			bCheck = false;
		}
	}
}

