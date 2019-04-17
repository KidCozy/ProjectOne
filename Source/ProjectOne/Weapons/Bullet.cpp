// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include "AI/AICharacter.h"
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
	Speed = 70.0f;

	LifeTime = 0.0f;

	Col->SetCollisionProfileName(TEXT("Bullet"));

	DirectionVector = GetActorForwardVector();
	SetActorScale3D(FVector(0.2f, 0.05f, 0.05f));

	Mesh->SetGenerateOverlapEvents(false);
	
	static ConstructorHelpers::FObjectFinder<UMaterial> MATERIAL(TEXT("Material'/Game/Materail/M_Projectile.M_Projectile'"));

	if (MATERIAL.Succeeded()) {
		Material = MATERIAL.Object;
	}

	Materialinstance = UMaterialInstanceDynamic::Create(Material, Mesh);
	Mesh->SetMaterial(0, Materialinstance);

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> DECALINS(TEXT("MaterialInstanceConstant'/Game/Materail/BulletScratch_Decal_Inst.BulletScratch_Decal_Inst'"));
	if (DECALINS.Succeeded()) {
		DecalMaterialinstance = DECALINS.Object;
	}

	Mesh->SetCollisionProfileName(TEXT("Bullet"));

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

	LifeTime += DeltaTime;
	if (LifeTime > 5.0f)
		Destroy(this);
}

void ABullet::OnCollisionOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OherCcomp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ABLOG_S(Warning);
	ABCHECK(GetOwner());
	//CreateDecal
	
	UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterialinstance,
			FVector(30.0f, 5.0f, 5.0f), this->GetActorLocation(),
		Normal.Rotation(), 100.0f);

	
	ABLOG(Warning, TEXT("Owner : %s"), *(GetOwner()->GetName()));
	ABLOG(Warning, TEXT("OtherActor : %s"), *(OtherActor->GetName()));

	//ABCHECK(IsValid(Cast<AProjectOneCharacter>(OtherActor)));
	auto Character = Cast<AProjectOneCharacter>(OtherActor);
	if (Character)
		Character->Hit(5.0f, GetOwner());

	//ABCHECK(IsValid(Cast<AAICharacter>(OtherActor)));
	auto AI = Cast<AAICharacter>(OtherActor);
	if (AI)
		AI->Hit(10.0f, GetOwner());



	Destroy(this);

}

void ABullet::SetDirection(FVector direction)
{
	DirectionVector = direction;
}

