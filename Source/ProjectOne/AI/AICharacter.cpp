// Fill out your copyright notice in the Description page of Project Settings.

#include "AICharacter.h"
#include "Weapons/Pistol.h"
#include "Weapons/Bullet.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
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

	MoveToLocation(FVector(1820.0f, -3520.0f, 226.0f));

	ABLOG(Warning,TEXT("TargetCoverPos : %f, %f ,%f"),TargetCoverPos.X, TargetCoverPos.Y, TargetCoverPos.Z )

	//RightDash();
	

	//GetController()->SetControlRotation()
	//GetController()->GetControlRotation();

	//GetController()

	//AddControllerYawInput(Rate * 45.0f * GetWorld()->GetDeltaSeconds());
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	FVector SpawnPos(100.0f, 0.0f, 50.0f);
	Weapone = GetWorld()->SpawnActor<AWeapon>(SpawnPos, FRotator::ZeroRotator);
	FAttachmentTransformRules test(EAttachmentRule::KeepRelative, false);
	Weapone->SetOwner(this);
	Weapone->AttachToActor(this, test);




	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	DrawDebugSphere(GetWorld(), GetActorLocation() + Direction * 2000.0f, 1800.0f, 16, FColor::Green, false, 2.0f);

	//GetMesh()->SetSimulatePhysics(false);


	//GetWorld()->GetTimerManager().SetTimer(Delay, this, &AAICharacter::LookAround, 3.0f, false);

	//LookAroundStart();
	CurState = AIState::Neutral;
	Detected();
	//NextCover();
	//Shot();


}

void AAICharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAICharacter::Forward()
{

	APAnim->Forward = 1.0f * 100.0f;
	// find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, 1.0f);


	CheckObstacle();
	

	if (DirectionVec == MoveVec::LeftVec)
		Left();
	else if (DirectionVec == MoveVec::RightVec)
		RIght();

	
}

void AAICharacter::Back()
{
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

	ABLOG_S(Warning);
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

	ABLOG_S(Warning);
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
	ABLOG_S(Warning);
	ABLOG(Warning, TEXT("LeftAngle : %f"), LeftAngle);
	ABLOG(Warning, TEXT("RightAngle : %f"), RightAngle);
	ABLOG(Warning, TEXT("Yaw : %f"), GetController()->GetControlRotation().Yaw);
	if (!LeftEnd)
	{
		GetController()->SetControlRotation(FRotator(0, FMath::Lerp(GetController()->GetControlRotation().Yaw, LeftAngle, 0.005f), 0));
		if (FMath::Abs(GetController()->GetControlRotation().Yaw - LeftAngle) < 2.0f)
			LeftEnd = true;
	}
	else
	{
		GetController()->SetControlRotation(FRotator(0, FMath::Lerp(GetController()->GetControlRotation().Yaw, RightAngle, 0.005f), 0));
		if (FMath::Abs(GetController()->GetControlRotation().Yaw - RightAngle) < 2.0f)
			LeftEnd = false;
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
			Weapone->Shot(Weapone->GetActorLocation(), SpreadVec);


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
	//if (TargetPlayer == NULL)
		//return FVector::ZeroVector;

	
	float distance = FVector::Distance(Weapone->GetActorLocation(), TargetPlayer->GetActorLocation());


	float time = distance / 20.0f;

	ABLOG(Warning,TEXT("%f"),time)

	FVector LookVec = TargetPlayer->GetActorLocation() + time * TargetPlayer->GetCharacterMovement()->GetLastInputVector().GetSafeNormal();

	ABLOG(Warning, TEXT("Input vec : %f, %f, %f"), TargetPlayer->GetCharacterMovement()->GetLastInputVector().GetSafeNormal().X, TargetPlayer->GetCharacterMovement()->GetLastInputVector().GetSafeNormal().Y, TargetPlayer->GetCharacterMovement()->GetLastInputVector().GetSafeNormal().Z);

	ABLOG(Warning, TEXT("LOOK Pos: %f, %f, %f"), LookVec.X, LookVec.Y, LookVec.Z);



	return LookVec;
}

void AAICharacter::Update()
{
	
	ABLOG(Warning, TEXT("isShoting :   %d"), isShooting);

	switch (CurState)
	{
	case AIState::Neutral:
		if (TargetPlayer != NULL) {
			CurState = AIState::Offensive;
			Shot();
		}

		Forward();

		break;
	case AIState::Offensive:


		if (TargetPlayer == NULL)
		{
			Shot();
			CurState = AIState::Neutral;
			return;
		}


		if (TargetPlayer != NULL) {
			LookAt(TargetPlayer->GetActorLocation());

			if (FVector::Distance(GetActorLocation(), TargetPlayer->GetActorLocation()) > 1500.0f)
				Forward();
			else
				RIght();
		}
		break;
	case AIState::Diffensive:
		break;
	default:
		break;
	}
}

void AAICharacter::MoveCover()
{
	if (IsMoving)
	{
		//if(DirectionVec ==MoveVec::ForwardVec)
		LookAt(TargetCoverPos);
		Forward();
		CheckSafe();
		ABLOG(Warning,TEXT("%f, %f, %f"),TargetCoverPos.X, TargetCoverPos.Y, TargetCoverPos.Z)
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
				ABLOG(Warning, TEXT("test debug"));
				continue;
			}


			if (TargetCover == NULL)
				TargetCover = DetectedCovers[i];

			if (FVector::Distance(GetActorLocation(), DetectedCovers[i]->GetActorLocation()) < FVector::Distance(GetActorLocation(), TargetCover->GetActorLocation()))
			{
				TargetCover = DetectedCovers[i];
			}

			ABLOG(Warning, TEXT("TargetCover : %s"), *TargetCover->GetName());
			ABLOG(Warning,TEXT("TargetCover Distance : %f"), FVector::Distance(TargetCover->GetActorLocation(), GetActorLocation()))
				
			
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

				if (FVector::Distance(GetActorLocation(), TargetCover->SafePos[i]) < FVector::Distance(GetActorLocation(), TargetCoverPos))
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
			ABLOG(Warning, TEXT("test debug"));
			continue;
		}


		if (TargetCover == NULL)
			TargetCover = DetectedCovers[i];

		if (FVector::Distance(GetActorLocation(), DetectedCovers[i]->GetActorLocation()) + FVector::Distance(DetectedCovers[i]->GetActorLocation(), Destination) < FVector::Distance(GetActorLocation(), TargetCover->GetActorLocation()) + FVector::Distance(TargetCover->GetActorLocation(), Destination))
		{
			TargetCover = DetectedCovers[i];
		}

		ABLOG(Warning, TEXT("TargetCover : %s"), *TargetCover->GetName());
		ABLOG(Warning, TEXT("TargetCover Distance : %f"), FVector::Distance(TargetCover->GetActorLocation(), GetActorLocation()))


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

			if (FVector::Distance(GetActorLocation(), TargetCover->SafePos[i]) < FVector::Distance(GetActorLocation(), TargetCoverPos))
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

	if (FVector::Distance(TargetCoverPos, GetActorLocation()) < 150.0f) {
		TargetCoverPos = FVector::ZeroVector;
		LookAt(TargetLocationPos);
		IsMoving = false;
		ABLOG_S(Warning);
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

		ABLOG(Warning, TEXT("Cover : %d"),DetectedCovers.Num())
		

			if (DetectedCovers.Num() > 1) {
				//LookAt(Location);
				NextCover(Location);
					MoveCover();
			}
			else 
			{
				LookAt(TargetLocationPos);
					Forward();
			}
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


	ABLOG(Warning, TEXT("TargetCover :  %s"), *TargetCover->GetName());

	for (int i = 0; i < TargetCover->SafePos.Num(); i++) 
	{
		DrawDebugLine(GetWorld(), Character->GetActorLocation() , TargetCover->SafePos[i], FColor::Green, false, 5.0f, 0, 1);
		if (GetWorld()->LineTraceSingleByChannel(OutHit, Character->GetActorLocation(), TargetCover->SafePos[i], ECC_Visibility, CollisionParams))
		{
			//DrawDebugLine(GetWorld(), Character->FollowCamera->GetComponentLocation(), TargetCover->SafePos[i], FColor::Green, false, 5.0f, 0, 1);
			if (OutHit.bBlockingHit)
			{
				DrawDebugLine(GetWorld(), Character->GetActorLocation(), TargetCover->SafePos[i], FColor::Red, false, 5.0f, 0, 1);
				if (TargetCoverPos == FVector::ZeroVector)
					TargetCoverPos = TargetCover->SafePos[i];

				if (FVector::Distance(TargetCover->SafePos[i], GetActorLocation()) < FVector::Distance(TargetCoverPos, GetActorLocation()))
					TargetCoverPos = TargetCover->SafePos[i];
			}
		}
	}

	ABLOG(Warning, TEXT("TargetCoverPos :  %f , %f, %f"), TargetCoverPos.X, TargetCoverPos.Y, TargetCoverPos.Z);
	if (TargetCoverPos != FVector::ZeroVector)
		//IsMoving = true;
		AICon->MoveToLocation(TargetCoverPos);
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


	DrawDebugSphere(GetWorld(), GetActorLocation(), 200.0f, 16, FColor::Red, false, 0.2f);

	if (bulletResult)
	{
		ABLOG(Warning, TEXT("Bullets"));

		ABullet * Bullet = Cast<ABullet>(OverlapBullets[0].GetActor());

		ABLOG(Warning, TEXT("Bullet Name : %s"), *Bullet->GetName());

		Hide(Bullet->GetOwner());
	}


	DetectedPlayers.Empty();
	DetectedCovers.Empty();

	TargetPlayer = NULL;
	if (bResult)
	{
		int i = 0;
		for (auto OverlapResult : OverlapResults)
		{
			AProjectOneCharacter * Player = Cast<AProjectOneCharacter>(OverlapResult.GetActor());
			ACover * Cover = Cast<ACover>(OverlapResult.GetActor());
			if (Player) {

				if (GetWorld()->LineTraceSingleByChannel(OutHit, FollowCamera->GetComponentLocation() + FollowCamera->GetForwardVector()*200.0f, Player->GetActorLocation(), ECC_Visibility, CollisionParams))
				{
					if (OutHit.bBlockingHit)
					{
						//ABLOG_S(Warning);
						DrawDebugLine(GetWorld(), FollowCamera->GetComponentLocation() + FollowCamera->GetForwardVector()*200.0f, Player->GetActorLocation(), FColor::Red, false, 0.2f, 0, 1);
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

					if (FVector::Distance(GetActorLocation(), Player->GetActorLocation()) < FVector::Distance(GetActorLocation(), TargetPlayer->GetActorLocation()))
					{
						TargetPlayer =Player;
					}

					i++;
					DrawDebugLine(GetWorld(), FollowCamera->GetComponentLocation() + FollowCamera->GetForwardVector()*200.0f, Player->GetActorLocation(), FColor::Green, false, 0.2f, 0, 1);
					//GEngine->AddOnScreenDebugMessage(i, 5.0f, FColor::Blue, *OverlapResult.GetActor()->GetName());
					DetectedPlayers.AddUnique(Player);
				}

			}

			if (Cover)
			{
				if (GetWorld()->LineTraceSingleByChannel(OutHit, FollowCamera->GetComponentLocation() + FollowCamera->GetForwardVector()*200.0f, Cover->GetActorLocation(), ECC_Visibility, CollisionParams))
				{
					if (OutHit.bBlockingHit)
					{
						//ABLOG_S(Warning);
						DrawDebugLine(GetWorld(), FollowCamera->GetComponentLocation() + FollowCamera->GetForwardVector()*200.0f, Cover->GetActorLocation(), FColor::Red, false, 0.2f, 0, 1);
						

						if (OutHit.GetActor()->GetActorLocation() == Cover->GetActorLocation())
						{
							//if (!TargetCover)
							//	TargetCover = Cover;

							//if (FVector::Distance(GetActorLocation(), Cover->GetActorLocation()) < FVector::Distance(GetActorLocation(), TargetCover->GetActorLocation()))
							//{
							//	TargetCover = Cover;
							//}

							i++;
							DrawDebugLine(GetWorld(), FollowCamera->GetComponentLocation() + FollowCamera->GetForwardVector()*200.0f, Cover->GetActorLocation(), FColor::Green, false, 0.2f, 0, 1);
							//GEngine->AddOnScreenDebugMessage(i, 5.0f, FColor::Blue, *OverlapResult.GetActor()->GetName());
							if (TargetLocationPos != FVector::ZeroVector)
							{
								if(FVector::Distance(GetActorLocation(), OutHit.GetActor()->GetActorLocation()) < FVector::Distance(GetActorLocation(), TargetLocationPos))
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
		//GEngine->AddOnScreenDebugMessage(i, 1.0f, FColor::Blue, *DetectedCovers[i]->GetName());
	//}

	if (PastCovers.Num() > 0) {
		for (int i = 0; i < PastCovers.Num(); i++) {
			GEngine->AddOnScreenDebugMessage(i, 1.0f, FColor::Blue, *PastCovers[i]->GetName());
		}
	}

	DrawDebugSphere(GetWorld(), GetActorLocation() + Direction * 2000.0f, 2000.0f, 16, FColor::Green, false, 0.2f);
}

void AAICharacter::CheckObstacle()
{
	FVector End;
	FVector LeftVec;

	End = GetActorForwardVector() * 500.0f;
	End = GetActorLocation() + End;

	FHitResult OutHit;
	FHitResult LeftHit;
	FCollisionQueryParams CollisionParams;


	if (GetWorld()->LineTraceSingleByChannel(OutHit, GetActorLocation(), End, ECC_Visibility, CollisionParams))
	{

		if (OutHit.bBlockingHit)
		{
			if (!FirstCheck) {
				FirstCheck = true;
				//ABLOG_S(Warning);
				DrawDebugLine(GetWorld(), GetActorLocation(), End, FColor::Red, false, 1, 0, 1);

				float tmp = GetActorForwardVector().Rotation().Yaw;
				tmp += 5.0f;
				//End = (GetActorForwardVector() + GetActorRightVector()) * 500.0f;
				End = FRotator(0.0f, tmp, 0.0f).Vector().GetSafeNormal()*550.f;
				End = GetActorLocation() + End;

				tmp = GetActorForwardVector().Rotation().Yaw;
				tmp -= 5.0f;
				LeftVec = FRotator(0.0f, tmp, 0.0f).Vector().GetSafeNormal()*550.f;
				LeftVec = GetActorLocation() + LeftVec;

				DrawDebugLine(GetWorld(), GetActorLocation(), LeftVec, FColor::Green, false, 1, 0, 1);

				if (GetWorld()->LineTraceSingleByChannel(OutHit, GetActorLocation(), End, ECC_Visibility, CollisionParams))
				{
					if (OutHit.bBlockingHit)
					{
						//ABLOG(Warning, TEXT("right enter"));
						if (GetWorld()->LineTraceSingleByChannel(LeftHit, GetActorLocation(), LeftVec, ECC_Visibility, CollisionParams))
						{
							//������ ���� �Ѵ� �¾�����
							if (LeftHit.bBlockingHit)
							{
							//	ABLOG(Warning, TEXT("right and left enter"));
								if (FMath::Abs(OutHit.Distance - LeftHit.Distance) < 10.0f)
								{
								//	ABLOG(Warning, TEXT("right and left same"));
									float rand = FMath::RandRange(0, 1);
									//ABLOG(Warning, TEXT("Rand : %f"), rand);
									if (rand > 0.5f)
										DirectionVec = MoveVec::RightVec;
									else
										DirectionVec = MoveVec::LeftVec;
								}
								else
								{
									if (OutHit.Distance > LeftHit.Distance)
										DirectionVec = MoveVec::RightVec;
									else
										DirectionVec = MoveVec::LeftVec;
								}

							}
						}
						else
						{
							DirectionVec = MoveVec::LeftVec;
						}
					}
				}
				else
				{
					if (GetWorld()->LineTraceSingleByChannel(LeftHit, GetActorLocation(), LeftVec, ECC_Visibility, CollisionParams))
					{
						//���ʸ� �¾�����
						//ABLOG(Warning, TEXT("left only"));
						DirectionVec = MoveVec::RightVec;
					}
					else
					{
						//�Ѵ� �ȸ¾�����
					//	ABLOG(Warning, TEXT("not"));
						float rand = FMath::RandRange(0, 1);
						//ABLOG(Warning, TEXT("Rand : %f"), rand);
						if (rand > 0.5f)
							DirectionVec = MoveVec::RightVec;
						else
							DirectionVec = MoveVec::LeftVec;
					}
				}

			}
		}
	}
	else
	{
		End = GetActorForwardVector() * 500.0f;
		End = GetActorLocation() + End;
		DrawDebugLine(GetWorld(), GetActorLocation(), End, FColor::Green, false, 1, 0, 1);
		FirstCheck = false;
		DirectionVec = MoveVec::ForwardVec;
	}
}

bool AAICharacter::CheckLocation(FVector Pos)
{
	return FVector::Distance(Pos, GetActorLocation()) < 50.0f;
}

void AAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AICon = Cast<AProjectOneAIController>(GetController());
}

AAICharacter::AAICharacter()
{
	SetResources();



	AIControllerClass = AProjectOneAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;



	static ConstructorHelpers::FObjectFinder<USkeletalMesh> AI_MESH(TEXT("SkeletalMesh'/Game/Animations/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));

	if (AI_MESH.Succeeded())
		GetMesh()->SetSkeletalMesh(AI_MESH.Object);

	static ConstructorHelpers::FClassFinder<UPlayerCharacterAnimInstance> AI_ANI(TEXT("AnimBlueprint'/Game/Animations/AnimationBlueprint/PlayerCharacter_AnimBP.PlayerCharacter_AnimBP_C'"));
	if (AI_ANI.Succeeded())
		GetMesh()->SetAnimInstanceClass(AI_ANI.Class);

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

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
	Hp = 100.0f;
}