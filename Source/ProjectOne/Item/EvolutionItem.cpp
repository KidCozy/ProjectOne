// Fill out your copyright notice in the Description page of Project Settings.

#include "EvolutionItem.h"
#include "AI/AICharacter.h"
#include "Weapons/Bullet.h"

// Sets default values
AEvolutionItem::AEvolutionItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Col = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));

	RootComponent = Mesh;

	Col->SetupAttachment(RootComponent);

	Col->SetRelativeLocation(FVector(0.0f, 0.0f, 30.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PJ_Mesh(TEXT("StaticMesh'/Game/BuildMap/NewFolder/Fruit/SM_Fruit_Dummy.SM_Fruit_Dummy'"));
	if (PJ_Mesh.Succeeded())
	{
		Mesh->SetStaticMesh(PJ_Mesh.Object);
	}

	//Mesh->SetSimulatePhysics

	/*Mesh->GetBodyInstance()->bLockXRotation = true;
	Mesh->GetBodyInstance()->bLockYRotation = true;
	Mesh->GetBodyInstance()->bLockZRotation = true;*/
}

// Called when the game starts or when spawned
void AEvolutionItem::BeginPlay()
{
	Super::BeginPlay();

	Col->OnComponentBeginOverlap.AddDynamic(this, &AEvolutionItem::OnCollisionOverlap);

}

// Called every frame
void AEvolutionItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEvolutionItem::OnCollisionOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OherCcomp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{



	ABCHECK(IsValid(Cast<AProjectOneCharacter>(OtherActor)));


	auto Character = Cast<AProjectOneCharacter>(OtherActor);
	if (Character) {
		Character->Evolution();

	}

	Destroy(this);
}

void AEvolutionItem::Drop()
{
	Mesh->SetSimulatePhysics(true);
}

