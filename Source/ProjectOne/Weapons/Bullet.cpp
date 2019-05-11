// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include "AI/AICharacter.h"
#include "Item/EvolutionItem.h"
#include "Kismet/GamePlayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Col = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	//Trail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail"));
	

	RootComponent = Mesh;

	Col->SetupAttachment(RootComponent);
	//Trail->SetupAttachment(RootComponent);
	//Trail->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PJ_Mesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (PJ_Mesh.Succeeded())
	{
		Mesh->SetStaticMesh(PJ_Mesh.Object);
	}

	Col->SetSphereRadius(50.0f);
	Speed = 70.0f;

	Col->SetCollisionProfileName(TEXT("Bullet"));

	DirectionVector = GetActorForwardVector();
	SetActorScale3D(FVector(0.2f, 0.05f, 0.05f));
	SetActorScale3D(GetActorScale()*3.0f);
	Mesh->SetGenerateOverlapEvents(false);
	
	static ConstructorHelpers::FObjectFinder<UMaterial> MATERIAL(TEXT("Material'/Game/Materail/NewMaterial.NewMaterial'"));

	if (MATERIAL.Succeeded()) {
		Material = MATERIAL.Object;
	}

	Materialinstance = UMaterialInstanceDynamic::Create(Material, Mesh);
	Mesh->SetMaterial(0, Materialinstance);

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> DECALINS(TEXT("MaterialInstanceConstant'/Game/Materail/BulletScratch_Decal_Inst.BulletScratch_Decal_Inst'"));
	if (DECALINS.Succeeded()) {
		DecalMaterialinstance = DECALINS.Object;
	}
	//static ConstructorHelpers::FObjectFinder<UParticleSystem> TRAIL(TEXT("ParticleSystem'/Game/particle/P_BulletRibbon_2.P_BulletRibbon_2'"));
	//if (TRAIL.Succeeded()) {
	//	Trail->SetTemplate(TRAIL.Object);
	//}
	
	//Trail->AutoAttachSocketName = TEXT("Middle");


	isStartRay = true;

	Mesh->SetCollisionProfileName(TEXT("Bullet"));
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->InitialSpeed = 50000.0f;
	LifeTime = 0.0f;
}

void ABullet::SetStartPos(FVector Position)
{
	PreLocation = Position;
}

//void ABullet::RayCheckFunc() {
//	if (!isDrawRay) {
//		FHitResult OutHit;
//		FCollisionQueryParams CollisionParam;
//
//		if (GetWorld()->LineTraceSingleByChannel(OutHit, PreLocation, GetActorLocation(), ECC_Pawn, CollisionParam)) {
//			auto Character = Cast<AProjectOneCharacter>(OutHit.Actor);
//			if (Character)
//				Character->Hit(5.0f, GetOwner());
//
//			auto AI = Cast<AAICharacter>(OutHit.Actor);
//			if (AI)
//				AI->Hit(10.0f, GetOwner());
//			Destroy(this);
//		}
//		isDrawRay = true;
//
//		DrawDebugLine(GetWorld(), PreLocation, GetActorLocation(), FColor::Red, false, 0.2f, 0, 1);
//	}
//	else if (isDrawRay) {
//		PreLocation = GetActorLocation();
//		isDrawRay = false;
//	}
//
//	//PreTimer += 0.01f;
//	//GetWorld()->GetTimerManager().ClearTimer(RayCheckTimer);
//}

void ABullet::PostInitializeComponents()
{
	Super::PostInitializeComponents();
//	Col->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnCollisionOverlap);
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	//GetWorld()->GetTimerManager().SetTimer(RayCheckTimer, this, &ABullet::RayCheckFunc, 0.1f, true);

}
// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult OutHit;
	FVector StartRay = GetActorLocation();
	FVector EndRay = (DirectionVector * 1000.0f) + GetActorLocation();
	FCollisionQueryParams CollisionParam;
	if (isStartRay) {
		StartRay = PreLocation;
		isStartRay = false;
	}

	if (GetWorld()->LineTraceSingleByChannel(OutHit, StartRay, EndRay, ECC_Pawn, CollisionParam)) {

		auto Character = Cast<AProjectOneCharacter>(OutHit.Actor);
		if (Character)
			Character->Hit(5.0f, GetOwner());

		auto AI = Cast<AAICharacter>(OutHit.Actor);
		if (AI)
			AI->Hit(10.0f, GetOwner());

		auto EvolutionItem = Cast<AEvolutionItem>(OutHit.Actor);
		if (EvolutionItem)
			EvolutionItem->Drop();

		Destroy(this);

	}

	//DrawDebugLine(GetWorld(), StartRay, EndRay, FColor::Red, false, 1.0f, 0, 1);
	LifeTime += DeltaTime;
	if (LifeTime > 5.0f)
		Destroy(this);

	
}
//
//void ABullet::OnCollisionOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OherCcomp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
//{
//	ABLOG_S(Warning);
//	ABCHECK(GetOwner());
//	//CreateDecal
//	
//	UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterialinstance,
//			FVector(30.0f, 5.0f, 5.0f), this->GetActorLocation(),
//		Normal.Rotation(), 100.0f);
//
//	
//	ABLOG(Warning, TEXT("Owner : %s"), *(GetOwner()->GetName()));
//	ABLOG(Warning, TEXT("OtherActor : %s"), *(OtherActor->GetName()));
//
//	//ABCHECK(IsValid(Cast<AProjectOneCharacter>(OtherActor)));
//	auto Character = Cast<AProjectOneCharacter>(OtherActor);
//	if (Character)
//		Character->Hit(5.0f, GetOwner());
//
//	//ABCHECK(IsValid(Cast<AAICharacter>(OtherActor)));
//	auto AI = Cast<AAICharacter>(OtherActor);
//	if (AI)
//		AI->Hit(10.0f, GetOwner());
//
//
//
//	Destroy(this);
//
//}

void ABullet::SetDirection(FVector direction)
{
	DirectionVector = direction;
	SetActorRotation(direction.Rotation());
}

