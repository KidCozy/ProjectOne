// Fill out your copyright notice in the Description page of Project Settings.

#include "AICharacter.h"
#include "Weapons/Pistol.h"
#include "Weapons/Bullet.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Runtime/NavigationSystem/Public/NavigationPath.h"
#include "Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/WidgetComponent.h"
#include "Components/Widget.h"
#include "ProjectOneAIController.h"


void AAICharacter::Tick(float delta)
{
	//Super::Tick(delta);

	//GetController()->GetControlRotation();


	 //FRotator rot = UKismetMathLibrary

	//Forward();
	//Left();


	//APAnim->Forward = -1.0f * 100.0f;
	// find out which way is forward
	//const FRotator Rotation = Controller->GetControlRotation();
	//const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	//const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	//AddMovementInput(-Direction, 1.0f);


	//FVector player = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	//FVector Camera = FollowCamera->GetComponentLocation();

	////ABLOG(Warning, TEXT("%f,%f,%f"), FollowCamera->GetComponentLocation().X, FollowCamera->GetComponentLocation().Y, FollowCamera->GetComponentLocation().Z);

	//FRotator rot = FRotationMatrix::MakeFromX(player - Camera).Rotator();

	//GetController()->SetControlRotation(rot);

	//DrawDebugLine(GetWorld(), player, GetActorLocation(), FColor::Green, false, 20.0f, 0, 1);


	Detected();
	//LookAt(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());

	//if (IsLookAround)
	//	LookAround();
	//Update();

	if (isShooting)
	{
		if (TargetPlayer != NULL) {
			//LookAt(TargetPlayer->GetActorLocation());
			LookAt(Prediction());
		}
		Shooting(delta);
	}
	
	/*if (DetectedCovers.Num() != 0) {
		LookAt(FVector(2740.0f, -2500.0f, 0.0f));
		if (IsLookTarget) {
			NextCover(FVector(2740.0f, -2500.0f, 0.0f));
			IsLookTarget = false;
		}
	
	}
	else
	{
		LookAt(FVector(2740.0f, -2500.0f, 0.0f));
		Forward();
	}
	MoveCover();*/

	//MoveCover();

	//MoveToLocation(FVector(6000.0f, -500.0f, 98.0f));

	//ABLOG(Warning,TEXT("TargetCoverPos : %f, %f ,%f"),TargetCoverPos.X, TargetCoverPos.Y, TargetCoverPos.Z )

	//RightDash();
	
	//Update();

	//GetController()->SetControlRotation()
	//GetController()->GetControlRotation();

	//GetController()

	//AddControllerYawInput(Rate * 45.0f * GetWorld()->GetDeltaSeconds());

	//ABLOG(Warning,TEXT("direction vec : %d"),DirectionVec);

	//ABLOG(Warning, TEXT("%d"), CurState);

	//ABLOG(Warning, TEXT("Target GetLandPosZ : %f"), GetLandPosZ(-612.0f, 1082.0f));
	//ABLOG(Warning, TEXT("Player GetLandPosZ : %f"), GetLandPosZ(-12000.0f, 21946.0f));
	if (GetLandPosZ(-14100.0f, 17200.0f) == 0.0f || TargetLocationPos.Z ==0.0f) {
		SetRandomLocation();
	}
	Update();
	//AICon->MoveToLocation(FVector(9200.0f, 11265.0f, 749.0f));
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	//FVector SpawnPos(100.0f, 0.0f, 50.0f);
	//Weapone = GetWorld()->SpawnActor<AWeapon>(SpawnPos, FRotator::ZeroRotator);
	//FAttachmentTransformRules test(EAttachmentRule::KeepRelative, false);
	//Weapone->SetOwner(this);
	//Weapone->AttachToActor(this, test);


	GetWorld()->GetTimerManager().SetTimer(Delay, this, &AAICharacter::CheckObstacle, 0.4f, false);
	GetWorld()->GetTimerManager().SetTimer(InitTime, this, &AAICharacter::InitTargetPlayer, 4.0f, false);
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	//DrawDebugSphere(GetWorld(), GetActorLocation() + Direction * 2000.0f, 1800.0f, 16, FColor::Green, false, 2.0f);

	//GetMesh()->SetSimulatePhysics(false);


	//GetWorld()->GetTimerManager().SetTimer(Delay, this, &AAICharacter::LookAround, 3.0f, false);

	//LookAroundStart();
	CurState = AIState::Neutral;
	Detected();
	//NextCover();
	//Shot();


	/*ABLOG(Warning, TEXT("TargetLocation :   %f, %f, %f"), TargetLocationPos.X, TargetLocationPos.Y, TargetLocationPos.Z);

	AICon->MoveToLocation(TargetCoverPos);*/


}

void AAICharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAICharacter::Forward()
{
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	APAnim->Forward = 1.0f * 100.0f;
	// find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	//ABLOG(Warning, TEXT("Direction Vec : %f, %f, %f"), Direction.X, Direction.Y, Direction.Z);

	//ABLOG(Warning, TEXT("Character Speed : %f, %f, %f"), GetVelocity().X, GetVelocity().Y, GetVelocity().Z);
	AddMovementInput(Direction, 1.0f);


	//GetWorld()->GetTimerManager().ClearTimer(Delay);

	//CheckObstacle();
	

	/*if (DirectionVec == MoveVec::LeftVec)
		Left();
	else if (DirectionVec == MoveVec::RightVec)
		RIght();*/

	
}

void AAICharacter::Back()
{
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	APAnim->Forward = -1.0f * 100.0f;
	// find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(-Direction, 1.0f);
}

void AAICharacter::Left()
{
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	//ABLOG_S(Warning);
	APAnim->Right = -1.0f * 100.0f;
	APAnim->Right = -1.0f * 100.0f;

	// find out which way is right
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get right vector 
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	//add movement in that direction
	AddMovementInput(-Direction, 1.0f);
}

void AAICharacter::RIght()
{
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	//ABLOG_S(Warning);
	APAnim->Right = 1.0f * 100.0f;

	// find out which way is right
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get right vector 
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	//add movement in that direction
	AddMovementInput(Direction, 1.0f);

}

void AAICharacter::LookAt(FVector LookPos)
{
	const FVector Camera = FollowCamera->GetComponentLocation();

	//ABLOG(Warning, TEXT("%f,%f,%f"), FollowCamera->GetComponentLocation().X, FollowCamera->GetComponentLocation().Y, FollowCamera->GetComponentLocation().Z);

	const FRotator rot = FRotationMatrix::MakeFromX(LookPos - Camera).Rotator();


	//ABLOG(Warning, TEXT("%f,%f,%f"), rot.Pitch,rot.Yaw,rot.Roll);

	GetController()->SetControlRotation(rot);	
}

void AAICharacter::LookAround()
{
	if (IsLookAround) {

		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;

		//ABLOG_S(Warning);
		//ABLOG(Warning, TEXT("LeftAngle : %f"), LeftAngle);
		//ABLOG(Warning, TEXT("RightAngle : %f"), RightAngle);
		//ABLOG(Warning, TEXT("Yaw : %f"), GetController()->GetControlRotation().Yaw);
		if (!LeftEnd)
		{
			GetController()->SetControlRotation(FRotator(0, FMath::Lerp(GetController()->GetControlRotation().Yaw, LeftAngle, 0.01f), 0));
			if (FMath::Abs(GetController()->GetControlRotation().Yaw - LeftAngle) < 20.0f) {
				LeftEnd = true;
				LookCount++;
			}
		}
		else
		{
			GetController()->SetControlRotation(FRotator(0, FMath::Lerp(GetController()->GetControlRotation().Yaw, RightAngle, 0.01f), 0));
			if (FMath::Abs(GetController()->GetControlRotation().Yaw - RightAngle) < 20.0f) {
				LeftEnd = false;
				LookCount++;
			}
		}

		if (LookCount > 1)
		{
			LookCount = 0;
			IsLookAround = false;
			SetRandomLocation();
			//PastCovers.Empty();
			MoveEnd = false;
		}

	}


	/*ABLOG_S(Warning);
	float rand = FMath::RandRange(-180, 180);

	FRotator rot(0, rand, 0);

	GetController()->SetControlRotation(rot);

	GetWorld()->GetTimerManager().SetTimer(Delay, this, &AAICharacter::LookAround, 3.0f, false);*/
}

void AAICharacter::LookAroundStart()
{
	IsLookAround = true;
	LeftAngle = GetController()->GetControlRotation().Yaw - 60.0f;
	RightAngle = GetController()->GetControlRotation().Yaw + 60.0f;
	LeftEnd = false;
}

void AAICharacter::Shooting(float tick)
{
	if (isShooting) {
		if (intervalTime >= Weapone->IntervalTime) {
			FTimerHandle time_;//bulletCheck
			if (Weapone->CurBulletCount <= 0)
			{
				ReLoad();
			}

			//Spread Bullet
			float RandPitch = FMath::RandRange(-(Weapone->Spread*0.5f), Weapone->Spread*0.5f);
			float RandYaw = FMath::RandRange(-(Weapone->Spread*0.5f), Weapone->Spread*0.5f);

			FRotator SpreadRotation = FRotator(
				GetCharacterToAimeVec().Rotation().Pitch + RandPitch,
				//GetCharacterToAimeVec().Rotation().Pitch,
				//GetCharacterToAimeVec().Rotation().Yaw, 0.0f);
				GetCharacterToAimeVec().Rotation().Yaw + RandYaw, 0.0f);

			FVector SpreadVec = SpreadRotation.Vector().GetSafeNormal();
			Weapone->Shot(GetMesh()->GetSocketLocation(TEXT("Muzzle")), SpreadRotation, ScratchNormal);


			//Recol
			float PitchVal = FMath::RandRange(Weapone->VerticalRecoil * 0.7f, Weapone->VerticalRecoil);
			float YawVal = FMath::RandRange(-Weapone->HorizonRecoil * 0.5f, Weapone->HorizonRecoil*0.5f);
			AddControllerPitchInput(-PitchVal);
			AddControllerYawInput(YawVal);
		}
		intervalTime -= tick;
		if (intervalTime <= 0.0f) {
			intervalTime = Weapone->IntervalTime;
		}
	}
}

FVector AAICharacter::Prediction()
{
	if (TargetPlayer == NULL)
		return FVector::ZeroVector;


	FRotator SpreadRotation = FRotator(
		GetCharacterToAimeVec().Rotation().Pitch ,
		//GetCharacterToAimeVec().Rotation().Pitch,
		//GetCharacterToAimeVec().Rotation().Yaw, 0.0f);
		GetCharacterToAimeVec().Rotation().Yaw, 0.0f);

	FVector SpreadVec = SpreadRotation.Vector().GetSafeNormal();



	
	float distance = FVector::Distance(Weapone->GetActorLocation(), TargetPlayer->GetActorLocation());


	//float time = distance / 5.0f;

	//ABLOG(Warning, TEXT("BUllet vector size :  %f, %f, %f"), (SpreadVec * 3000.0f).X, (SpreadVec * 3000.0f).Y, (SpreadVec * 3000.0f).Z);

	float test = (TargetPlayer->GetVelocity() - (SpreadVec * 50000.0f)).Size();

	//ABLOG(Warning, TEXT("Velocity : %f, %f ,%f"), TargetPlayer->GetVelocity().X, TargetPlayer->GetVelocity().Y, TargetPlayer->GetVelocity().Z);

	//ABLOG(Warning, TEXT("test : %f"), test);

	float time = distance / test;

	//float time = FVector::DotProduct((TargetPlayer->GetActorLocation() - Weapone->GetActorLocation()), SpreadVec * Weapone->Speed);

	//ABLOG(Warning,TEXT("Time :  %f"),time)

	FVector LookVec = TargetPlayer->GetActorLocation() + time * TargetPlayer->GetVelocity();

	//ABLOG(Warning, TEXT("Input vec : %f, %f, %f"), TargetPlayer->GetCharacterMovement()->GetLastInputVector().GetSafeNormal().X *600, TargetPlayer->GetCharacterMovement()->GetLastInputVector().GetSafeNormal().Y *600, TargetPlayer->GetCharacterMovement()->GetLastInputVector().GetSafeNormal().Z * 600);

	//ABLOG(Warning, TEXT("LOOK Pos: %f, %f, %f"), LookVec.X, LookVec.Y, LookVec.Z);



	return LookVec;
}

void AAICharacter::Update()
{
	if (isShooting && !APAnim->Montage_IsPlaying(APAnim->ShotMontage))
	{
		//ABLOG(Warning, TEXT("PlayMontage"));
		APAnim->Montage_Play(APAnim->ShotMontage);

	}
	else if(!isShooting)
	{
		//ABLOG(Warning, TEXT("!PlayMontage"));
		APAnim->Montage_Stop(0.5f, APAnim->ShotMontage);
		

	}

	if (isShooting && !APAnim->Montage_IsPlaying(APAnim->SecondShotMontage))
	{
		APAnim->Montage_Play(APAnim->SecondShotMontage);
	}
	else if (!isShooting)
	{
		APAnim->Montage_Stop(0.5f, APAnim->SecondShotMontage);
	}


	//ABLOG(Warning, TEXT("isShooting :   %d"), isShooting);

	//ABLOG(Warning, TEXT("STATE : %d"), CurState);
	
	//ABLOG(Warning, TEXT("TargetLocation :   %f, %f, %f"), TargetLocationPos.X, TargetLocationPos.Y, TargetLocationPos.Z);
	if (IsAlive) {
		switch (CurState)
		{
		case AIState::Neutral:
			//if (TargetLocationPos !=FVector::ZeroVector) {


			if (!MoveEnd)
				MoveToLocation(TargetLocationPos);
			else
				LookAround();

			//}

			break;
		case AIState::Offensive:

			AICon->StopMovement();
			if (!isShooting)
				Shot();

			if (TargetPlayer == NULL)
			{
				Shot();
				PastCovers.Empty();
				MoveEnd = false;
				SetRandomLocation();
				CurState = AIState::Neutral;
				return;
			}


			if (TargetPlayer != NULL) {
				//LookAt(TargetPlayer->GetActorLocation());
				LookAt(Prediction());
				if (Distance(GetActorLocation(), TargetPlayer->GetActorLocation()) > 1500.0f)
					Forward();
				else
					RIght();


				if (Hp<40.0f && TargetPlayer->Hp > Hp)
					CurState = AIState::Diffensive;
			}
			break;
		case AIState::Diffensive:

			if (TargetPlayer == NULL)
			{
				if (isShooting)
					Shot();
				PastCovers.Empty();
				MoveEnd = false;
				SetRandomLocation();
				CurState = AIState::Neutral;
				return;
			}

			if (TargetPlayer != NULL) {

				//LookAt(TargetPlayer->GetActorLocation());
				Back();
			}

			break;
		case AIState::Guard:
			if (TargetPlayer != NULL) {


				if (Distance(TargetPlayer->GetActorLocation(), GetActorLocation()) > 3000.0f)
					MoveToLocation(TargetPlayer->GetActorLocation());
				else
					LookAt(TargetPlayer->GetActorLocation());
			}
			else {
				CurState = AIState::Neutral;
			}
			break;
		default:
			break;
		}
	}
	else
		isShooting = false;
}

void AAICharacter::MoveCover()
{
	if (IsMoving)
	{

		if (DirectionVec == MoveVec::ForwardVec && RigthCheck && LeftCheck) {
			//LookAt(TargetCoverPos);
			//ABLOG(Warning, TEXT("Look Target"));
		}
			//AICon->MoveToLocation(TargetCoverPos);

		AICon->MoveToLocation(TargetLocationPos);
		//AICon->MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn());
		//Forward();
		CheckSafe();
		//ABLOG(Warning,TEXT("TargetCoverPos : %f, %f, %f"),TargetCoverPos.X, TargetCoverPos.Y, TargetCoverPos.Z)
	}
}

void AAICharacter::NextCover()
{
	if (IsMoving)
		return;

	TargetCover = NULL;

		for (int i = 0; i<DetectedCovers.Num(); i++)
		{
		/*	if (FVector::Distance(DetectedCovers[i]->GetActorLocation(), GetActorLocation()) < 250.0f) {
				ABLOG_S(Warning);
				if(i != DetectedCovers.Num()-1)
				TargetCover = NULL;
				continue;
			}*/

			if (PastCovers.Contains(DetectedCovers[i])) {
				//ABLOG(Warning, TEXT("test debug"));
				continue;
			}


			if (TargetCover == NULL)
				TargetCover = DetectedCovers[i];

			if (Distance(GetActorLocation(), DetectedCovers[i]->GetActorLocation()) < Distance(GetActorLocation(), TargetCover->GetActorLocation()))
			{
				TargetCover = DetectedCovers[i];
			}

			//ABLOG(Warning, TEXT("TargetCover : %s"), *TargetCover->GetName());
			//ABLOG(Warning,TEXT("TargetCover Distance : %f"), Distance(TargetCover->GetActorLocation(), GetActorLocation()))
				
			
			//ABLOG(Warning, TEXT("%f"), IsMoving);
			
		}


		if (TargetCover) {

			if (PastCovers.Num() > 2)
			{
				PastCovers.RemoveAt(0);
			}
			PastCovers.Add(TargetCover);

			for (int i = 0; i < TargetCover->SafePos.Num(); i++)
			{
				if (TargetCoverPos == FVector::ZeroVector)
					TargetCoverPos = TargetCover->SafePos[i];

				if (Distance(GetActorLocation(), TargetCover->SafePos[i]) < Distance(GetActorLocation(), TargetCoverPos))
				{
					TargetCoverPos = TargetCover->SafePos[i];
				}
			}

			IsMoving = true;
		}



		//ABLOG(Warning, TEXT("TargetCover : %s"), *TargetCover->GetName());

		/*if (PastCovers.Num() > 2)
		{
			PastCovers.RemoveAt(2);
		}

		PastCovers.Push(TargetCover);*/


}

void AAICharacter::NextCover(FVector Destination)
{
	if (IsMoving)
		return;

	LookAt(Destination);

	TargetCover = NULL;

	for (int i = 0; i < DetectedCovers.Num(); i++)
	{
		/*	if (FVector::Distance(DetectedCovers[i]->GetActorLocation(), GetActorLocation()) < 250.0f) {
				ABLOG_S(Warning);
				if(i != DetectedCovers.Num()-1)
				TargetCover = NULL;
				continue;
			}*/

		if (PastCovers.Contains(DetectedCovers[i])) {
			//ABLOG(Warning, TEXT("test debug"));
			continue;
		}


		if (TargetCover == NULL)
			TargetCover = DetectedCovers[i];

		if (Distance(GetActorLocation(), DetectedCovers[i]->GetActorLocation()) + Distance(DetectedCovers[i]->GetActorLocation(), Destination) < Distance(GetActorLocation(), TargetCover->GetActorLocation()) + Distance(TargetCover->GetActorLocation(), Destination))
		{
			TargetCover = DetectedCovers[i];
		}

		//ABLOG(Warning, TEXT("TargetCover : %s"), *TargetCover->GetName());
		//ABLOG(Warning, TEXT("TargetCover Distance : %f"), Distance(TargetCover->GetActorLocation(), GetActorLocation()))


			//ABLOG(Warning, TEXT("%f"), IsMoving);

	}


	if (TargetCover) {

		if (PastCovers.Num() > 2)
		{
			PastCovers.RemoveAt(0);
		}
		PastCovers.Add(TargetCover);

		for (int i = 0; i < TargetCover->SafePos.Num(); i++)
		{
			if (TargetCoverPos == FVector::ZeroVector)
				TargetCoverPos = TargetCover->SafePos[i];

			if (Distance(GetActorLocation(), TargetCover->SafePos[i]) < Distance(GetActorLocation(), TargetCoverPos))
			{
				TargetCoverPos = TargetCover->SafePos[i];
			}
		}

		IsMoving = true;
	}


}

void AAICharacter::CheckSafe()
{
	if (!IsMoving)
		return;

	if (Distance(TargetCoverPos, GetActorLocation()) < 70.0f) {
		//ABLOG(Warning, TEXT("Distance : %f"), Distance(TargetCoverPos, GetActorLocation()));
		TargetCoverPos = FVector::ZeroVector;
		LookAt(TargetLocationPos);
		IsMoving = false;

		//NextCover();
	}
}

void AAICharacter::CheckSafe(FVector Destination)
{

}

void AAICharacter::MoveToLocation(FVector Location)
{
	if (!CheckLocation(Location)) {


		TargetLocationPos = Location;

		//ABLOG(Warning, TEXT("Cover : %d"),DetectedCovers.Num())
		

			if (DetectedCovers.Num() > 1 && TargetCover) {
				NextCover(Location);
				MoveCover();
			}
			else 
			{
				/*if(DirectionVec == MoveVec::ForwardVec && LeftCheck && RigthCheck)
				LookAt(TargetLocationPos);
				Forward();*/

			//	ABLOG_S(Warning);

				//ABLOG(Warning,TEXT("TargetLocation : %f, %f, %f"), TargetLocationPos.X, TargetLocationPos.Y, TargetLocationPos.Z)

				AICon->MoveToLocation(TargetLocationPos);
				//AICon->MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn());
			}
	}
	else if (Hiding)
	{
		Hiding = false;
		MoveEnd = true;
		//LookAroundStart();

		CurState = AIState::Guard;
	}
	else
	{
		MoveEnd = true;
		LookAroundStart();
	}
}

void AAICharacter::Hide(AActor * Attacker)
{
	ABCHECK(IsValid(TargetCover))
	ABCHECK(IsValid(Cast<AProjectOneCharacter>(Attacker)));
	auto Character = Cast<AProjectOneCharacter>(Attacker);

	FHitResult OutHit;
	FCollisionQueryParams CollisionParams;

	IsMoving = false;
	TargetCoverPos = FVector::ZeroVector;


	//ABLOG(Warning, TEXT("Hide TargetCover :  %s"), *TargetCover->GetName());

	for (int i = 0; i < TargetCover->SafePos.Num(); i++) 
	{
		//DrawDebugLine(GetWorld(), Character->FollowCamera->GetComponentLocation(), TargetCover->SafePos[i], FColor::Green, false, 5.0f, 0, 1);
		if (GetWorld()->LineTraceSingleByChannel(OutHit, Character->FollowCamera->GetComponentLocation(), TargetCover->SafePos[i], ECC_Visibility, CollisionParams))
		{
			//DrawDebugLine(GetWorld(), Character->FollowCamera->GetComponentLocation(), TargetCover->SafePos[i], FColor::Green, false, 5.0f, 0, 1);
			if (OutHit.bBlockingHit)
			{
				//DrawDebugLine(GetWorld(), Character->FollowCamera->GetComponentLocation(), TargetCover->SafePos[i], FColor::Red, false, 5.0f, 0, 1);
				if (TargetCoverPos == FVector::ZeroVector)
					TargetCoverPos = TargetCover->SafePos[i];

				if (Distance(TargetCover->SafePos[i], GetActorLocation()) < Distance(TargetCoverPos, GetActorLocation()))
					TargetCoverPos = TargetCover->SafePos[i];
			}
		}
	}

	//ABLOG(Warning, TEXT("TargetCoverPos :  %f , %f, %f"), TargetCoverPos.X, TargetCoverPos.Y, TargetCoverPos.Z);
	if (TargetCoverPos != FVector::ZeroVector) {
		//IsMoving = true;
		TargetLocationPos = TargetCoverPos;
		Hiding = true;
		TargetPlayer = Character;
	}
		//AICon->MoveToLocation(TargetCoverPos);
}

void AAICharacter::SetRandomLocation()
{
	LookAt(FVector(0.0f, 0.0f, 1150.0f));
	TargetLocationPos = FVector::ZeroVector;
	Detected();


	float rand = FMath::RandRange(4000.0f, 7000.0f);
	FVector MaxLocation = GetActorForwardVector() * rand;

	

	if (DetectedCovers.Num() > 1) {
		for (int i = 0; i < DetectedCovers.Num(); i++)
		{
			if (PastCovers.Contains(DetectedCovers[i]))
				continue;

			if (DetectedCovers[i]->SafePos.Num() > 0) {
				if (TargetLocationPos == FVector::ZeroVector) {

					TargetLocationPos = DetectedCovers[i]->SafePos[1];
					continue;
				}

				if (Distance(GetActorLocation(), DetectedCovers[i]->GetActorLocation()) > Distance(GetActorLocation(), TargetLocationPos))
				{
					if (Distance(GetActorLocation(), TargetLocationPos) < Distance(GetActorLocation(), MaxLocation))
						TargetLocationPos = DetectedCovers[i]->SafePos[1];
				}
			}
		}
	}
	//TargetLocationPos = FVector(MaxLocation.X, MaxLocation.Y, 1150.0f);

	//while (GetLandPosZ(9200.0f, 11265.0f) == 0.0f) {
	if(GetLandPosZ(-14100.0f, 17200.0f)!=0.0f)
		TargetLocationPos = FVector(-14100.0f, 17200.0f, GetLandPosZ(-14100.0f, 17200.0f));
	//}
}

void AAICharacter::Attacked(AActor * Attacker)
{
	switch (CurState)
	{
	case Neutral:

		if (TargetCover) {
			if(Distance(TargetCover->GetActorLocation(),GetActorLocation()) < 1500.0f)
			Hide(Attacker);
			MoveEnd = false;
		}
		else
		{
			ABLOG(Warning, TEXT("Attacked"));
			MoveEnd = true;
			AICon->StopMovement();
			LookAt(Attacker->GetActorLocation());
		}
		//else
		//{
		//	ABLOG(Warning, TEXT("Hide No CoverPos"));
		//	LookAt(Attacker->GetActorLocation());
		//}


		break;
	default:
		break;
	}
}

void AAICharacter::FindPlayer()
{

	switch (CurState)
	{
	case Neutral:
		if (Distance(TargetPlayer->GetActorLocation(), GetActorLocation()) > 6000.0f)
			return;
		//if (!MoveEnd)
		//	TargetLocationPos = TargetCoverPos;
		//else
		//{
		else {
			auto targetPlayer = Cast<AAICharacter>(TargetPlayer);

			if (targetPlayer)
			{
				if (targetPlayer->TargetPlayer == this) {
					CurState = AIState::Offensive;
					
				}
				else
					CurState = AIState::Guard;
			}
			else
			{
				CurState = AIState::Guard;
			}
		}
		//}
		break;
	case Offensive:
		break;
	case Diffensive:
		break;
	case Guard:

		auto targetPlayer = Cast<AAICharacter>(TargetPlayer);

		if (targetPlayer)
		{
			if (targetPlayer->TargetPlayer == this)
				CurState = AIState::Offensive;

			if (Distance(TargetPlayer->GetActorLocation(), GetActorLocation()) < 3000.0f)
				CurState = AIState::Offensive;

		}
		else 
		{
			if (Distance(TargetPlayer->GetActorLocation(), GetActorLocation()) < 3000.0f)
				CurState = AIState::Offensive;
		}

				//if (FVector::Distance(TargetPlayer->GetActorLocation(), GetActorLocation()) > 2000.0f)

			break;
	}
}

void AAICharacter::InitTargetPlayer()
{
	TargetPlayer = NULL;
	Detected();


	GetWorld()->GetTimerManager().SetTimer(InitTime, this, &AAICharacter::InitTargetPlayer, 4.0f, false);

}

float AAICharacter::GetLandPosZ(float PosX, float PosY)
{
	FHitResult OutHit;

	FVector StartPos(PosX,PosY,27000.0f);
	FVector EndPos(PosX, PosY, 0.0f);

	FCollisionQueryParams CollisionParams;

	

		if (GetWorld()->LineTraceSingleByChannel(OutHit, StartPos, EndPos, ECC_GameTraceChannel3, CollisionParams))
		{
			if (OutHit.bBlockingHit)
			{

				UNavigationSystemV1* navSys = UNavigationSystemV1::GetCurrent(GetWorld());

				UNavigationPath* NavPath = navSys->FindPathToLocationSynchronously(GetWorld(), GetActorLocation() , FVector(PosX, PosY, OutHit.ImpactPoint.Z), NULL);

				//NavPath->EnableDebugDrawing(NavPath,FLinearColor::Red);

			//	ABLOG(Warning, TEXT("Path Num : %d"), NavPath->PathPoints.Num());
				//if (NavPath->PathPoints.Num() > 0)
					//ABLOG(Warning, TEXT("Path Target : %f, %f, %f"), NavPath->PathPoints[NavPath->PathPoints.Num()-1].X, NavPath->PathPoints[NavPath->PathPoints.Num() - 1].Y, NavPath->PathPoints[NavPath->PathPoints.Num() - 1].Z);

				//NavPath->GetDebugString();

				if (NavPath->PathPoints.Num() > 0)
				{
					float TargetNum = NavPath->PathPoints.Num()-1;
					if (PosX == NavPath->PathPoints[TargetNum].X && PosY == NavPath->PathPoints[TargetNum].Y)
						return OutHit.ImpactPoint.Z;
					else
						return 0.0f;
				}
				else
				{
					return 0.0f;
				}
				//if (!NavPath->IsPartial())
				//	return 0.0f;
				//else
				//return OutHit.ImpactPoint.Z;
			}
			else
				return 0.0f;
		}
		else
		{
			return 0.0f;
		}


	
}



void AAICharacter::Detected()
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	bool bResult = GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		GetActorLocation() + Direction * 2000.0f,
		FQuat::Identity,
		ECollisionChannel::ECC_Pawn,
		FCollisionShape::MakeSphere(2000.0f),
		CollisionQueryParam
	);

	TArray<FOverlapResult> OverlapBullets;
	FCollisionQueryParams CollisionQuery(NAME_None, false, this);

	bool bulletResult = GetWorld()->OverlapMultiByChannel(
		OverlapBullets,
		GetActorLocation(),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(200.0f),
		CollisionQuery
		);


	FHitResult OutHit;
	FHitResult LeftHit;
	FCollisionQueryParams CollisionParams;


	//DrawDebugSphere(GetWorld(), GetActorLocation(), 200.0f, 16, FColor::Red, false, 0.2f);

	if (bulletResult)
	{
		//ABLOG(Warning, TEXT("Bullets"));

		ABullet * Bullet = Cast<ABullet>(OverlapBullets[0].GetActor());

		//ABLOG(Warning, TEXT("Bullet Name : %s"), *Bullet->GetName());



		Attacked(Bullet->GetOwner());
		//Hide(Bullet->GetOwner());
	}


	DetectedPlayers.Empty();
	DetectedCovers.Empty();

	//TargetPlayer = NULL;
	if (bResult)
	{
		int i = 0;
		for (auto OverlapResult : OverlapResults)
		{
			AProjectOneCharacter * Player = Cast<AProjectOneCharacter>(OverlapResult.GetActor());
			ACover * Cover = Cast<ACover>(OverlapResult.GetActor());
			if (Player) {
				if (Player->IsAlive) {
					if (GetWorld()->LineTraceSingleByChannel(OutHit, FollowCamera->GetComponentLocation() + FollowCamera->GetForwardVector()*200.0f, Player->GetActorLocation(), ECC_Visibility, CollisionParams))
					{
						if (OutHit.bBlockingHit)
						{
							//ABLOG_S(Warning);
							//DrawDebugLine(GetWorld(), FollowCamera->GetComponentLocation() + FollowCamera->GetForwardVector()*200.0f, Player->GetActorLocation(), FColor::Red, false, 0.2f, 0, 1);
							DetectedPlayers.Remove(Player);
							/*i++;
							DrawDebugLine(GetWorld(), FollowCamera->GetComponentLocation(), Player->GetActorLocation(), FColor::Green, false, 1, 0, 1);
							GEngine->AddOnScreenDebugMessage(i, 5.0f, FColor::Blue, *OverlapResult.GetActor()->GetName());*/
						}
					}
					else
					{
						if (!TargetPlayer)
							TargetPlayer = Player;

						if (TargetPlayer) {
							if (Distance(GetActorLocation(), Player->GetActorLocation()) < Distance(GetActorLocation(), TargetPlayer->GetActorLocation()))
							{
								TargetPlayer = Player;
							}
						}

						i++;
						//DrawDebugLine(GetWorld(), FollowCamera->GetComponentLocation() + FollowCamera->GetForwardVector()*200.0f, Player->GetActorLocation(), FColor::Green, false, 0.2f, 0, 1);
						//GEngine->AddOnScreenDebugMessage(i, 5.0f, FColor::Blue, *OverlapResult.GetActor()->GetName());
						DetectedPlayers.AddUnique(Player);
						FindPlayer();
					}

				}
			}

			if (Cover)
			{
				if (GetWorld()->LineTraceSingleByChannel(OutHit, FollowCamera->GetComponentLocation() + FollowCamera->GetForwardVector()*200.0f, Cover->GetActorLocation(), ECC_Visibility, CollisionParams))
				{
					if (OutHit.bBlockingHit)
					{
						//ABLOG_S(Warning);
						//DrawDebugLine(GetWorld(), FollowCamera->GetComponentLocation() + FollowCamera->GetForwardVector()*200.0f, Cover->GetActorLocation(), FColor::Red, false, 0.2f, 0, 1);
						

						if (OutHit.GetActor()->GetActorLocation() == Cover->GetActorLocation())
						{
							//if (!TargetCover)
							//	TargetCover = Cover;

							//if (FVector::Distance(GetActorLocation(), Cover->GetActorLocation()) < FVector::Distance(GetActorLocation(), TargetCover->GetActorLocation()))
							//{
							//	TargetCover = Cover;
							//}

							i++;
							//DrawDebugLine(GetWorld(), FollowCamera->GetComponentLocation() + FollowCamera->GetForwardVector()*200.0f, Cover->GetActorLocation(), FColor::Green, false, 0.2f, 0, 1);
							//GEngine->AddOnScreenDebugMessage(i, 5.0f, FColor::Blue, *OverlapResult.GetActor()->GetName());
							if (TargetLocationPos != FVector::ZeroVector)
							{
								if(Distance(GetActorLocation(), OutHit.GetActor()->GetActorLocation()) < Distance(GetActorLocation(), TargetLocationPos))
									DetectedCovers.AddUnique(Cover);

							}
							else
							DetectedCovers.AddUnique(Cover);
						}
						else
						{
							DetectedCovers.Remove(Cover);
						}
						/*i++;
						DrawDebugLine(GetWorld(), FollowCamera->GetComponentLocation(), Player->GetActorLocation(), FColor::Green, false, 1, 0, 1);
						GEngine->AddOnScreenDebugMessage(i, 5.0f, FColor::Blue, *OverlapResult.GetActor()->GetName());*/
					}
				}
			}
		}
	}

	//for (int i = 0; i < DetectedPlayers.Num(); i++) {
	//	GEngine->AddOnScreenDebugMessage(i, 1.0f, FColor::Blue, *DetectedPlayers[i]->GetName());
	//}

	//for (int i = 0; i < DetectedCovers.Num(); i++) {
	//	GEngine->AddOnScreenDebugMessage(i, 1.0f, FColor::Blue, *DetectedCovers[i]->GetName());
	//}

	//if (PastCovers.Num() > 0) {
	//	for (int i = 4; i < PastCovers.Num()+4; i++) {
	//		GEngine->AddOnScreenDebugMessage(i, 1.0f, FColor::Yellow, *PastCovers[i-4]->GetName());
	//	}
	//}

	//DrawDebugSphere(GetWorld(), GetActorLocation() + Direction * 2000.0f, 2000.0f, 16, FColor::Green, false, 0.2f);
}

void AAICharacter::CheckObstacle()
{
	FVector End;
	FVector LeftVec;
	FVector RightVec;

	End = GetActorForwardVector() * 50.0f;
	End = GetActorLocation() + End;

	FHitResult OutHit;
	FHitResult LeftHit;
	FCollisionQueryParams CollisionParams;

	//ABLOG_S(Warning);

	if (GetWorld()->LineTraceSingleByChannel(OutHit, GetActorLocation(), End, ECC_Visibility, CollisionParams))
	{

		if (OutHit.bBlockingHit)
		{
			if (!FirstCheck) {
				FirstCheck = true;
				//ABLOG_S(Warning);
				//DrawDebugLine(GetWorld(), GetActorLocation(), End, FColor::Red, false, 1, 0, 1);

				float tmp = GetActorForwardVector().Rotation().Yaw;
				tmp += 45.0f;
				//End = (GetActorForwardVector() + GetActorRightVector()) * 500.0f;
				End = FRotator(0.0f, tmp, 0.0f).Vector().GetSafeNormal()*550.f;
				End = GetActorLocation() + End;

				tmp = GetActorForwardVector().Rotation().Yaw;
				tmp -= 45.0f;
				LeftVec = FRotator(0.0f, tmp, 0.0f).Vector().GetSafeNormal()*550.f;
				LeftVec = GetActorLocation() + LeftVec;

				//DrawDebugLine(GetWorld(), GetActorLocation(), LeftVec, FColor::Green, false, 1, 0, 1);

				if (GetWorld()->LineTraceSingleByChannel(OutHit, GetActorLocation(), End, ECC_Visibility, CollisionParams))
				{
					if (OutHit.bBlockingHit)
					{
						//ABLOG(Warning, TEXT("right enter"));
						if (GetWorld()->LineTraceSingleByChannel(LeftHit, GetActorLocation(), LeftVec, ECC_Visibility, CollisionParams))
						{
							//오른쪽 왼쪽 둘다 맞았을때
							if (LeftHit.bBlockingHit)
							{
							//	ABLOG(Warning, TEXT("right and left enter"));
								if (FMath::Abs(OutHit.Distance - LeftHit.Distance) < 10.0f)
								{
								//	ABLOG(Warning, TEXT("right and left same"));
									float rand = FMath::RandRange(0, 1);
									//ABLOG(Warning, TEXT("Rand : %f"), rand);
									if (rand > 0.5f) {
										DirectionVec = MoveVec::RightVec;
										LookAt(End);
									}
									else {
										DirectionVec = MoveVec::LeftVec;
										LookAt(LeftVec);
									}
								}
								else
								{
									if (OutHit.Distance > LeftHit.Distance) {
										DirectionVec = MoveVec::RightVec;
										LookAt(End);
									}
									else {
										DirectionVec = MoveVec::LeftVec;
										LookAt(LeftVec);
									}
								}

							}
						}
						else
						{
							DirectionVec = MoveVec::LeftVec;
							LookAt(LeftVec);
						}
					}
				}
				else
				{
					if (GetWorld()->LineTraceSingleByChannel(LeftHit, GetActorLocation(), LeftVec, ECC_Visibility, CollisionParams))
					{
						//왼쪽만 맞았을때
						//ABLOG(Warning, TEXT("left only"));
						DirectionVec = MoveVec::RightVec;
						LookAt(End);
					}
					else
					{
					//	//둘다 안맞았을때
					////	ABLOG(Warning, TEXT("not"));
					//	float rand = FMath::RandRange(0, 1);
					//	//ABLOG(Warning, TEXT("Rand : %f"), rand);
					//	if (rand > 0.5f) {
					//		DirectionVec = MoveVec::RightVec;
					//		LookAt(End);
					//	}F
					//	else {
					//		DirectionVec = MoveVec::LeftVec;
					//		LookAt(LeftVec);
					//	}
					}
				}

			}
		}
	}
	else
	{
		End = GetActorForwardVector() * 500.0f;
		End = GetActorLocation() + End;
		//DrawDebugLine(GetWorld(), GetActorLocation(), End, FColor::Green, false, 1, 0, 1);
		FirstCheck = false;
		DirectionVec = MoveVec::ForwardVec;
	}

	float tmp = GetActorForwardVector().Rotation().Yaw;
	tmp += 60.0f;
	//End = (GetActorForwardVector() + GetActorRightVector()) * 500.0f;
	RightVec = FRotator(0.0f, tmp, 0.0f).Vector().GetSafeNormal()*550.f;
	RightVec = GetActorLocation() + End;

	tmp = GetActorForwardVector().Rotation().Yaw;
	tmp -= 60.0f;
	LeftVec = FRotator(0.0f, tmp, 0.0f).Vector().GetSafeNormal()*550.f;
	LeftVec = GetActorLocation() + LeftVec;

	if (GetWorld()->LineTraceSingleByChannel(OutHit, GetActorLocation(), RightVec, ECC_Visibility, CollisionParams))
	{
		if (OutHit.bBlockingHit)
		{
			RigthCheck = false;
		}
	}
	else
	{
		RigthCheck = true;
	}

	if (GetWorld()->LineTraceSingleByChannel(OutHit, GetActorLocation(), LeftVec, ECC_Visibility, CollisionParams))
	{
		if (OutHit.bBlockingHit)
		{
			LeftCheck = false;
		}
	}
	else
	{
		LeftCheck = true;
	}

	GetWorld()->GetTimerManager().SetTimer(Delay, this, &AAICharacter::CheckObstacle, 0.4f, false);

}

float AAICharacter::Distance(FVector Vec1, FVector Vec2)
{

	return FMath::Sqrt(FMath::Pow((Vec1.X - Vec2.X), 2) + FMath::Pow((Vec1.Y - Vec2.Y), 2));

}

bool AAICharacter::CheckLocation(FVector Pos)
{
	return Distance(Pos, GetActorLocation()) < 50.0f;
}

void AAICharacter::SetResources()
{
	static ConstructorHelpers::FClassFinder<UCameraShake> CSHAKE_FIRE(TEXT("Blueprint'/Game/ScreenFX/CShake_Fire.CShake_Fire_C'"));
	if (CSHAKE_FIRE.Succeeded())
		CShakeList.Add(CSHAKE_FIRE.Class);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MANEQUIN(TEXT("SkeletalMesh'/Game/Animations/Wolf1/SK_Wolf1_Idle.SK_Wolf1_Idle'"));
	if (SK_MANEQUIN.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SK_MANEQUIN.Object);
		FirstMesh = SK_MANEQUIN.Object;
		SecondMeshComponent->SetSkeletalMesh(FirstMesh);
	}

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -42.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FClassFinder<UAnimInstance> TEMP_ANIM(TEXT("AnimBlueprint'/Game/Animations/Wolf1/BP_Wolf1.BP_Wolf1_C'"));
	if (TEMP_ANIM.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(TEMP_ANIM.Class);
		SecondMeshComponent->SetAnimInstanceClass(TEMP_ANIM.Class);
	}



	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Sec(TEXT("SkeletalMesh'/Game/Animations/Wolf2Build/SK_Wolf2_Idle.SK_Wolf2_Idle'"));
	if (SK_Sec.Succeeded()) {
		SecondSkMesh = SK_Sec.Object;
		//SecondMeshComponent->SetSkeletalMesh(SecondSkMesh);
		SecondMeshComponent->SetVisibility(false);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_THIRD(TEXT("SkeletalMesh'/Game/Animations/Wolf3Build/SK_Wolf3_Idle.SK_Wolf3_Idle'"));
	if (SK_THIRD.Succeeded()) {
		ThirdMesh = SK_THIRD.Object;
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_Sec(TEXT("AnimBlueprint'/Game/Animations/Wolf2Build/BP_Wolf2_Animation.BP_Wolf2_Animation_C'"));
	if (ANIM_Sec.Succeeded()) {
		SecondAnimIns = ANIM_Sec.Class;
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_THIRD(TEXT("AnimBlueprint'/Game/Animations/Wolf3Build/BP_Wolf3_Animation.BP_Wolf3_Animation_C'"));
	if (ANIM_THIRD.Succeeded()) {
		ThirdAnimIns = ANIM_THIRD.Class;
	}

	//유년기 Material 설정

	Mat.Add(GetMesh()->GetMaterial(0));
	Mat.Add(GetMesh()->GetMaterial(1));
	Mat.Add(GetMesh()->GetMaterial(2));

	DynamicShader.Add(GetMesh()->CreateDynamicMaterialInstance(0, Mat[0]));
	DynamicShader.Add(SecondMeshComponent->CreateDynamicMaterialInstance(0, Mat[0]));

	DynamicShader.Add(GetMesh()->CreateDynamicMaterialInstance(1, Mat[1]));
	DynamicShader.Add(SecondMeshComponent->CreateDynamicMaterialInstance(1, Mat[1]));

	DynamicShader.Add(GetMesh()->CreateDynamicMaterialInstance(2, Mat[2]));
	DynamicShader.Add(SecondMeshComponent->CreateDynamicMaterialInstance(2, Mat[2]));

	GetMesh()->SetMaterial(0, DynamicShader[0]);
	SecondMeshComponent->SetMaterial(0, DynamicShader[1]);

	GetMesh()->SetMaterial(1, DynamicShader[2]);
	SecondMeshComponent->SetMaterial(1, DynamicShader[3]);

	GetMesh()->SetMaterial(2, DynamicShader[4]);
	SecondMeshComponent->SetMaterial(3, DynamicShader[5]);



	DynamicShader[0]->SetScalarParameterValue("Amount", 0.0f);
	DynamicShader[0]->SetScalarParameterValue("EmissiveAmount", 150.0f);
	DynamicShader[0]->SetScalarParameterValue("Fringe", 40.0f);
	DynamicShader[0]->SetScalarParameterValue("Offset", 3.5f);
	DynamicShader[0]->SetScalarParameterValue("TransitionTime", 3.0f);

	DynamicShader[0]->SetVectorParameterValue("GlowColor", FLinearColor::FLinearColor(0.2f, 0.3f, 0.8f));

	DynamicShader[1]->SetScalarParameterValue("Amount", 0.5f);
	DynamicShader[1]->SetScalarParameterValue("EmissiveAmount", 150.0f);
	DynamicShader[1]->SetScalarParameterValue("Fringe", 40.0f);
	DynamicShader[1]->SetScalarParameterValue("Offset", 3.5f);
	DynamicShader[1]->SetScalarParameterValue("TransitionTime", 3.0f);

	DynamicShader[1]->SetVectorParameterValue("GlowColor", FLinearColor::FLinearColor(0.2f, 0.3f, 0.8f));


	DynamicShader[2]->SetScalarParameterValue("Amount", 0.0f);
	DynamicShader[2]->SetScalarParameterValue("EmissiveAmount", 150.0f);
	DynamicShader[2]->SetScalarParameterValue("Fringe", 40.0f);
	DynamicShader[2]->SetScalarParameterValue("Offset", 3.5f);
	DynamicShader[2]->SetScalarParameterValue("TransitionTime", 3.0f);

	DynamicShader[2]->SetVectorParameterValue("GlowColor", FLinearColor::FLinearColor(0.2f, 0.3f, 0.8f));

	DynamicShader[3]->SetScalarParameterValue("Amount", 0.5f);
	DynamicShader[3]->SetScalarParameterValue("EmissiveAmount", 150.0f);
	DynamicShader[3]->SetScalarParameterValue("Fringe", 40.0f);
	DynamicShader[3]->SetScalarParameterValue("Offset", 3.5f);
	DynamicShader[3]->SetScalarParameterValue("TransitionTime", 3.0f);

	DynamicShader[3]->SetVectorParameterValue("GlowColor", FLinearColor::FLinearColor(0.2f, 0.3f, 0.8f));

	DynamicShader[4]->SetScalarParameterValue("Amount", 0.0f);
	DynamicShader[4]->SetScalarParameterValue("EmissiveAmount", 150.0f);
	DynamicShader[4]->SetScalarParameterValue("Fringe", 40.0f);
	DynamicShader[4]->SetScalarParameterValue("Offset", 3.5f);
	DynamicShader[4]->SetScalarParameterValue("TransitionTime", 3.0f);

	DynamicShader[4]->SetVectorParameterValue("GlowColor", FLinearColor::FLinearColor(0.2f, 0.3f, 0.8f));

	DynamicShader[5]->SetScalarParameterValue("Amount", 0.5f);
	DynamicShader[5]->SetScalarParameterValue("EmissiveAmount", 150.0f);
	DynamicShader[5]->SetScalarParameterValue("Fringe", 40.0f);
	DynamicShader[5]->SetScalarParameterValue("Offset", 3.5f);
	DynamicShader[5]->SetScalarParameterValue("TransitionTime", 3.0f);

	DynamicShader[5]->SetVectorParameterValue("GlowColor", FLinearColor::FLinearColor(0.2f, 0.3f, 0.8f));




	static ConstructorHelpers::FObjectFinder<UMaterialInstance> EVOLUTION_END_MATERIAL(TEXT("MaterialInstanceConstant'/Game/Animations/Wolf2Build/Material/Barrier_Invert_Micro_2_Inst.Barrier_Invert_Micro_2_Inst'"));
	if (EVOLUTION_END_MATERIAL.Succeeded()) {

		ABLOG(Warning, TEXT("TEST"));

		GetMesh()->SetMaterial(3, EVOLUTION_END_MATERIAL.Object);
		SecondMeshComponent->SetMaterial(3, EVOLUTION_END_MATERIAL.Object);

		Mat.Add(GetMesh()->GetMaterial(3));

		DynamicShader.Add(GetMesh()->CreateDynamicMaterialInstance(3, Mat[3]));
		DynamicShader.Add(SecondMeshComponent->CreateDynamicMaterialInstance(3, Mat[3]));

		GetMesh()->SetMaterial(3, DynamicShader[6]);
		SecondMeshComponent->SetMaterial(3, DynamicShader[7]);


		DynamicShader[6]->SetScalarParameterValue("Amount", 0.5f);
		DynamicShader[6]->SetScalarParameterValue("EmissiveAmount", 150.0f);
		DynamicShader[6]->SetScalarParameterValue("Fringe", 40.0f);
		DynamicShader[6]->SetScalarParameterValue("Offset", 3.5f);
		DynamicShader[6]->SetScalarParameterValue("TransitionTime", 3.0f);

		DynamicShader[6]->SetVectorParameterValue("GlowColor", FLinearColor::FLinearColor(0.2f, 0.3f, 0.8f));

		DynamicShader[7]->SetScalarParameterValue("Amount", 0.5f);
		DynamicShader[7]->SetScalarParameterValue("EmissiveAmount", 150.0f);
		DynamicShader[7]->SetScalarParameterValue("Fringe", 40.0f);
		DynamicShader[7]->SetScalarParameterValue("Offset", 3.5f);
		DynamicShader[7]->SetScalarParameterValue("TransitionTime", 3.0f);

		DynamicShader[7]->SetVectorParameterValue("GlowColor", FLinearColor::FLinearColor(0.2f, 0.3f, 0.8f));
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> EVOLUTION_THIRDDOWN_MATERIAL(TEXT("MaterialInstanceConstant'/Game/Animations/Wolf3Build/Material/M_Wolf3EvolutionMat_Down_Inst.M_Wolf3EvolutionMat_Down_Inst'"));
	if (EVOLUTION_THIRDDOWN_MATERIAL.Succeeded())
	{

		GetMesh()->SetMaterial(4, EVOLUTION_THIRDDOWN_MATERIAL.Object);
		SecondMeshComponent->SetMaterial(4, EVOLUTION_THIRDDOWN_MATERIAL.Object);

		Mat.Add(GetMesh()->GetMaterial(4));

		DynamicShader.Add(GetMesh()->CreateDynamicMaterialInstance(4, Mat[4]));
		DynamicShader.Add(SecondMeshComponent->CreateDynamicMaterialInstance(4, Mat[4]));

		GetMesh()->SetMaterial(4, DynamicShader[8]);
		SecondMeshComponent->SetMaterial(4, DynamicShader[9]);

		DynamicShader[8]->SetScalarParameterValue("Amount", 0.6f);
		DynamicShader[8]->SetScalarParameterValue("EmissiveAmount", 150.0f);
		DynamicShader[8]->SetScalarParameterValue("Fringe", 40.0f);
		DynamicShader[8]->SetScalarParameterValue("Offset", 3.5f);
		DynamicShader[8]->SetScalarParameterValue("TransitionTime", 3.0f);

		DynamicShader[8]->SetVectorParameterValue("GlowColor", FLinearColor::FLinearColor(0.2f, 0.3f, 0.8f));

		DynamicShader[9]->SetScalarParameterValue("Amount", 0.6f);
		DynamicShader[9]->SetScalarParameterValue("EmissiveAmount", 150.0f);
		DynamicShader[9]->SetScalarParameterValue("Fringe", 40.0f);
		DynamicShader[9]->SetScalarParameterValue("Offset", 3.5f);
		DynamicShader[9]->SetScalarParameterValue("TransitionTime", 3.0f);

		DynamicShader[9]->SetVectorParameterValue("GlowColor", FLinearColor::FLinearColor(0.2f, 0.3f, 0.8f));
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> EVOLUTION_THIRDUP_MATERIAL(TEXT("MaterialInstanceConstant'/Game/Animations/Wolf3Build/Material/M_Wolf3EvolutionMat_Up_Inst.M_Wolf3EvolutionMat_Up_Inst'"));
	if (EVOLUTION_THIRDUP_MATERIAL.Succeeded()) {

		GetMesh()->SetMaterial(5, EVOLUTION_THIRDUP_MATERIAL.Object);
		SecondMeshComponent->SetMaterial(5, EVOLUTION_THIRDUP_MATERIAL.Object);

		Mat.Add(GetMesh()->GetMaterial(5));


		DynamicShader.Add(GetMesh()->CreateDynamicMaterialInstance(5, Mat[5]));
		DynamicShader.Add(SecondMeshComponent->CreateDynamicMaterialInstance(5, Mat[5]));

		GetMesh()->SetMaterial(5, DynamicShader[10]);
		SecondMeshComponent->SetMaterial(5, DynamicShader[11]);


		DynamicShader[10]->SetScalarParameterValue("Amount", 0.6f);
		DynamicShader[10]->SetScalarParameterValue("EmissiveAmount", 150.0f);
		DynamicShader[10]->SetScalarParameterValue("Fringe", 40.0f);
		DynamicShader[10]->SetScalarParameterValue("Offset", 3.5f);
		DynamicShader[10]->SetScalarParameterValue("TransitionTime", 3.0f);

		DynamicShader[10]->SetVectorParameterValue("GlowColor", FLinearColor::FLinearColor(0.2f, 0.3f, 0.8f));

		DynamicShader[11]->SetScalarParameterValue("Amount", 0.6f);
		DynamicShader[11]->SetScalarParameterValue("EmissiveAmount", 150.0f);
		DynamicShader[11]->SetScalarParameterValue("Fringe", 40.0f);
		DynamicShader[11]->SetScalarParameterValue("Offset", 3.5f);
		DynamicShader[11]->SetScalarParameterValue("TransitionTime", 3.0f);

		DynamicShader[11]->SetVectorParameterValue("GlowColor", FLinearColor::FLinearColor(0.2f, 0.3f, 0.8f));
	}



	GetMesh()->SetRelativeScale3D(FVector(0.7f, 0.7f, 0.7f));
	SecondMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -42.0f));
	SecondMeshComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

}

void AAICharacter::Evolution()
{

	if (IsAlive) {
		switch (CurLevel) {
		case 0:
			SecondMeshComponent->SetVisibility(true);
			/* 여기에 변화하는 코드 추가 */
		/*	SecondMeshComponent->SetAnimInstanceClass(SecondAnimIns);

			APAnim = Cast<UPlayerCharacterAnimInstance>(SecondMeshComponent->GetAnimInstance());
			GetCapsuleComponent()->SetCapsuleSize(35.0f, 70.0f);

			SecondMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -70.0f));
			SecondMeshComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

			CameraBoom->SocketOffset = FVector(100.0f, 50.0f, 90.0f);
			SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));*/

			/*종료되면 첫번째 스켈레탈 메쉬는 가리고 세 번째 메쉬를 로드시킴*/
			APAnim = Cast<UPlayerCharacterAnimInstance>(SecondMeshComponent->GetAnimInstance());
			GetWorld()->GetTimerManager().SetTimer(EvolutionTimer, this, &AAICharacter::SetAmount, 0.01f, true);
			break;
		case 1:
			GetMesh()->SetVisibility(true);

			/*SecondMeshComponent->SetAnimInstanceClass(SecondAnimIns);
			APAnim = Cast<UPlayerCharacterAnimInstance>(SecondMeshComponent->GetAnimInstance());

			SecondMeshComponent->SetVisibility(true);

			GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -70.0f));*/
			APAnim = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance());
			GetWorld()->GetTimerManager().SetTimer(EvolutionTimer, this, &AAICharacter::SetAmount, 0.01f, true);
			break;
		case 2:

			SecondMeshComponent->SetSkeletalMesh(SecondSkMesh);


			SecondMeshComponent->SetAnimInstanceClass(SecondAnimIns);

			APAnim = Cast<UPlayerCharacterAnimInstance>(SecondMeshComponent->GetAnimInstance());

			GetCapsuleComponent()->SetCapsuleSize(35.0f, 70.0f);

			GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -70.0f));
			GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

			SecondMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -70.0f));
			SecondMeshComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

			CameraBoom->SocketOffset = FVector(100.0f, 50.0f, 90.0f);

			GetWorld()->GetTimerManager().SetTimer(EvolutionTimer, this, &AAICharacter::SetAmount, 0.01f, true);
			break;

		case 3:

			GetMesh()->SetAnimInstanceClass(SecondAnimIns);
			GetMesh()->SetSkeletalMesh(SecondSkMesh);

			GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -70.0f));
			GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

			GetWorld()->GetTimerManager().SetTimer(EvolutionTimer, this, &AAICharacter::SetAmount, 0.01f, true);
			break;

		case 4:
			SecondMeshComponent->SetRelativeScale3D(FVector(1.3f, 1.3f, 1.3f));
			GetWorld()->GetTimerManager().SetTimer(EvolutionTimer, this, &AAICharacter::SetAmount, 0.01f, true);

			break;

		case 5:
			GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
			GetMesh()->SetSkeletalMesh(ThirdMesh);

			GetWorld()->GetTimerManager().SetTimer(EvolutionTimer, this, &AAICharacter::SetAmount, 0.01f, true);
			break;
		}
	}

}

void AAICharacter::SetAmount()
{
	switch (CurLevel)
	{
	case 0:
		if (curAmount < 1.0f || 0.0f < SecCurAmount) {
			curAmount += 0.01f;
			SecCurAmount -= 0.01f;

			if (curAmount > 1.0f)
				curAmount = 1.0f;

			if (SecCurAmount < 0.0f)
				SecCurAmount = 0.0f;

			SetScalarParameter(GetMesh(), 0, 0, curAmount);
			SetScalarParameter(GetMesh(), 1, 0, curAmount);
			SetScalarParameter(GetMesh(), 2, 0, curAmount);
			SetScalarParameter(SecondMeshComponent, 0, 0, SecCurAmount);
			SetScalarParameter(SecondMeshComponent, 1, 0, SecCurAmount);
			SetScalarParameter(SecondMeshComponent, 2, 0, SecCurAmount);
		}
		else {

			++CurLevel;

			GetWorld()->GetTimerManager().ClearTimer(EvolutionTimer);

			GetMesh()->SetRelativeScale3D(FVector(1.2f, 1.2f, 1.2f));

			curAmount = 0.5;
			Hp = 150.0f;
			MaxHp = 150.0f;
		}
		break;
	case 1:
		if (curAmount > 0.0f || SecCurAmount < 1.0f) {
			curAmount -= 0.01f;
			SecCurAmount += 0.01f;

			if (curAmount < 0.0f)
				curAmount = 0.0f;

			if (SecCurAmount > 1.0f)
				SecCurAmount = 1.0f;

			SetScalarParameter(GetMesh(), 0, 0, curAmount);
			SetScalarParameter(GetMesh(), 1, 0, curAmount);
			SetScalarParameter(GetMesh(), 2, 0, curAmount);
			SetScalarParameter(SecondMeshComponent, 0, 0, SecCurAmount);
			SetScalarParameter(SecondMeshComponent, 1, 0, SecCurAmount);
			SetScalarParameter(SecondMeshComponent, 2, 0, SecCurAmount);
		}
		else {
			//APAnim->Evolution();

			++CurLevel;

			SecCurAmount = 0.5;

			SetScalarParameter(SecondMeshComponent, 3, 0, SecCurAmount);
			SetScalarParameter(SecondMeshComponent, 4, 0, 1.0f);
			SetScalarParameter(SecondMeshComponent, 5, 0, 1.0f);

			SecondMeshComponent->SetMaterial(0, SecondMeshComponent->GetMaterial(3));
			SecondMeshComponent->SetMaterial(1, SecondMeshComponent->GetMaterial(4));
			SecondMeshComponent->SetMaterial(2, SecondMeshComponent->GetMaterial(5));


			Hp = 200.0f;
			MaxHp = 200.0f;
			GetWorld()->GetTimerManager().ClearTimer(EvolutionTimer);

			//GetMesh()->SetSkeletalMesh(ThirdMesh);
			//Weapone->IntervalTime = 0.06f;

		}
		break;

	case 2:
		if (curAmount < 1.0f || 0.0f < SecCurAmount)
		{
			curAmount += 0.01f;
			SecCurAmount -= 0.01f;

			if (curAmount > 1.0f)
				curAmount = 1.0f;

			if (SecCurAmount < 0.0f)
				SecCurAmount = 0.0f;

			SetScalarParameter(GetMesh(), 0, 0, curAmount);
			SetScalarParameter(GetMesh(), 1, 0, curAmount);
			SetScalarParameter(GetMesh(), 2, 0, curAmount);
			SetScalarParameter(SecondMeshComponent, 0, 0, SecCurAmount);
		}
		else {

			++CurLevel;
			curAmount = 0.5f;

			SetScalarParameter(GetMesh(), 3, 0, curAmount);
			SetScalarParameter(GetMesh(), 4, 0, 1.0f);
			SetScalarParameter(GetMesh(), 5, 0, 1.0f);

			GetMesh()->SetMaterial(0, GetMesh()->GetMaterial(3));
			GetMesh()->SetMaterial(1, GetMesh()->GetMaterial(4));
			GetMesh()->SetMaterial(2, GetMesh()->GetMaterial(5));

			Hp = 250.0f;
			MaxHp = 250.0f;
			Weapone->IntervalTime = 0.06f;
			GetWorld()->GetTimerManager().ClearTimer(EvolutionTimer);
		}
		break;

	case 3:
		if (curAmount > 0.0f || SecCurAmount < 1.0f) {
			curAmount -= 0.01f;
			SecCurAmount += 0.01f;

			if (curAmount < 0.0f)
				curAmount = 0.0f;

			if (SecCurAmount > 1.0f)
				SecCurAmount = 1.0f;

			SetScalarParameter(GetMesh(), 0, 0, curAmount);
			SetScalarParameter(SecondMeshComponent, 0, 0, SecCurAmount);

		}
		else
		{
			++CurLevel;
			SecCurAmount = 0.5;

			Hp = 300.0f;
			MaxHp = 300.0f;

			GetWorld()->GetTimerManager().ClearTimer(EvolutionTimer);
		}
		break;

	case 4:
		if (curAmount < 1.0f || 0.0f < SecCurAmount)
		{
			curAmount += 0.01f;
			SecCurAmount -= 0.01f;

			if (curAmount > 1.0f)
				curAmount = 1.0f;

			if (SecCurAmount < 0.0f)
				SecCurAmount = 0.0f;

			SetScalarParameter(GetMesh(), 0, 0, curAmount);
			SetScalarParameter(SecondMeshComponent, 0, 0, SecCurAmount);
		}
		else {
			++CurLevel;
			curAmount = 0.6;

			Hp = 350.0f;
			MaxHp = 350.0f;

			SetScalarParameter(GetMesh(), 0, 0, curAmount);
			SetScalarParameter(GetMesh(), 1, 0, curAmount);

			GetMesh()->SetMaterial(0, GetMesh()->GetMaterial(1));
			GetMesh()->SetMaterial(1, GetMesh()->GetMaterial(2));

			GetWorld()->GetTimerManager().ClearTimer(EvolutionTimer);
		}
		break;

	case 5:
		if (curAmount > 0.0f || SecCurAmount < 1.0f) {
			curAmount -= 0.01f;
			SecCurAmount += 0.01f;

			if (curAmount < 0.0f)
				curAmount = 0.0f;

			if (SecCurAmount > 1.0f)
				SecCurAmount = 1.0f;

			SetScalarParameter(GetMesh(), 0, 0, curAmount);
			SetScalarParameter(GetMesh(), 1, 0, curAmount);
			SetScalarParameter(SecondMeshComponent, 0, 0, SecCurAmount);

		}
		else {
			++CurLevel;

			Hp = 400.0f;
			MaxHp = 400.0f;
			GetWorld()->GetTimerManager().ClearTimer(EvolutionTimer);
		}

		break;
	}

}

void AAICharacter::SetWidget(UUserWidget * widget)
{
	HPBarWidgetComponent->SetWidget(widget);
	HPBarWidgetComponent->SetDrawSize(FVector2D(200.0f, 10.0f));
}

void AAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AICon = Cast<AProjectOneAIController>(GetController());


}

AAICharacter::AAICharacter()
{

	AIControllerClass = AProjectOneAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;



	static ConstructorHelpers::FObjectFinder<USkeletalMesh> AI_MESH(TEXT("SkeletalMesh'/Game/Animations/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));

	if (AI_MESH.Succeeded())
		GetMesh()->SetSkeletalMesh(AI_MESH.Object);

	static ConstructorHelpers::FClassFinder<UPlayerCharacterAnimInstance> AI_ANI(TEXT("AnimBlueprint'/Game/Animations/AnimationBlueprint/PlayerCharacter_AnimBP.PlayerCharacter_AnimBP_C'"));
	if (AI_ANI.Succeeded())
		GetMesh()->SetAnimInstanceClass(AI_ANI.Class);

	//GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	APAnim = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance());

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;



	GetMesh()->SetWorldRotation(FRotator(0.0f, 270.0f,0.0f ));
	GetMesh()->SetWorldLocation(FVector(0.0f, 0.0, -97.0f));


	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	//CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller


	//FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	FollowCamera->SetRelativeLocation(FVector(-50.0f, 0, 0));


	CameraBoom->TargetArmLength = 350.0f;
	CameraBoom->SocketOffset = FVector(40.0f, 50.0f, 60.0f);

	DirectionVec = MoveVec::ForwardVec;
	FirstCheck = false;

	Hp = 200.0f;
	HPBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidgetComponent"));

	HPBarWidgetComponent->SetupAttachment(GetCapsuleComponent());

	HPBarWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	HPBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);

	SetResources();
}
