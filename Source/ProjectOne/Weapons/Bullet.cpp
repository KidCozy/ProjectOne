// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Col = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));

	RootComponent = Mesh;

	Col->SetupAttachment(RootComponent);



	static ConstructorHelpers::FObjectFinder<UStaticMesh> PJ_Mesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (PJ_Mesh.Succeeded())
	{
		Mesh->SetStaticMesh(PJ_Mesh.Object);
	}


	Col->SetSphereRadius(50.0f);
	Speed = 10.0f;

	DirectionVector = GetActorForwardVector();
	SetActorScale3D(FVector(0.1f, 0.1f, 0.1f));

	Mesh->SetGenerateOverlapEvents(false);
}

void ABullet::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Col->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnCollisionOverlap);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorWorldOffset(DirectionVector * Speed);
}

void ABullet::OnCollisionOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OherCcomp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ABLOG_S(Warning);
	ABLOG(Warning, TEXT("Owner : %s"), *(GetOwner()->GetName()));
	ABLOG(Warning, TEXT("OtherActor : %s"), *(OtherActor->GetName()));

	ABCHECK(IsValid(Cast<AProjectOneCharacter>(OtherActor)));
	auto Character = Cast<AProjectOneCharacter>(OtherActor);
	Character->Hit(20.0f, GetOwner());

	Destroy(this);
}

void ABullet::SetDirection(FVector direction)
{
	DirectionVector = direction;
}

