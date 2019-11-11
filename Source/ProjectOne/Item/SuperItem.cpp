// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperItem.h"
#include "ProjectOne/Player/ProjectOneCharacter.h"
#include "ProjectOne/Player/POComponents/InventoryComponent.h"

// Sets default values
ASuperItem::ASuperItem()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Particle1 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PARTICLE SLOT"));
	Col = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	
	InitAssets();
	RootComponent = Mesh;

	SetActorScale3D(FVector(1.0f));
	SetActorRelativeScale3D(FVector(1.0f));

	Col->SetupAttachment(RootComponent);
	Col->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));

	Mesh->SetCollisionProfileName("NoCollision");
}

// Called when the game starts or when spawned
void ASuperItem::BeginPlay()
{
	Super::BeginPlay();
	Col->OnComponentBeginOverlap.AddDynamic(this, &ASuperItem::OnCollisionOverlap);
	
}

void ASuperItem::InitAssets()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MESH(TEXT("StaticMesh'/Game/BuildMap/NewFolder/Item_jar/SM_Item_jar.SM_Item_jar'"));
	if (MESH.Succeeded())
		Mesh->SetStaticMesh(MESH.Object);
}


void ASuperItem::OnCollisionOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OherCcomp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ABCHECK(IsValid(Cast<AProjectOneCharacter>(OtherActor)));
	auto Character = Cast<AProjectOneCharacter>(OtherActor);
	if (Character) {
		Character->Inventory->SetItem(this);
		Col->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Mesh->SetVisibility(false);
		SetNewOwner(Character);
	}
}

void ASuperItem::Duration()
{
	DurationTime--;
	if (DurationTime < 1)
	{
		DurationEnd();
		GetWorldTimerManager().ClearTimer(DurationTimer);
	}
}

