// Fill out your copyright notice in the Description page of Project Settings.

#include "WolfCharacter.h"
#include "Weapons/Pistol.h"

AWolfCharacter::AWolfCharacter(){
	SetResources();
}

void AWolfCharacter::SetResources() {
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
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -45.0f));
	SecondMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -45.0f));
	SecondMeshComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	CameraBoom->SocketOffset = FVector(240.0f, 40.0f, 50.0f);
}

void AWolfCharacter::Evolution() {
	if (IsAlive) {
		tmpLevel++;
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
			CameraBoom->SocketOffset = FVector(190.0f, 40.0f, 70.0f);
			Hp = 250.0f;
			MaxHp = 250.0f;
			GetWorld()->GetTimerManager().SetTimer(EvolutionTimer, this, &AWolfCharacter::SetAmount, 0.01f, true);
			break;
		case 1:
			GetMesh()->SetVisibility(true);

			/*SecondMeshComponent->SetAnimInstanceClass(SecondAnimIns);
			APAnim = Cast<UPlayerCharacterAnimInstance>(SecondMeshComponent->GetAnimInstance());

			SecondMeshComponent->SetVisibility(true);

			GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -70.0f));*/
			APAnim = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance());
			CameraBoom->SocketOffset = FVector(160.0f, 40.0f, 90.0f);
			Hp = 300.0f;
			MaxHp = 300.0f;
			GetWorld()->GetTimerManager().SetTimer(EvolutionTimer, this, &AWolfCharacter::SetAmount, 0.01f, true);
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

			Hp = 350.0f;
			MaxHp = 350.0f;
			GetWorld()->GetTimerManager().SetTimer(EvolutionTimer, this, &AWolfCharacter::SetAmount, 0.01f, true);
			break;

		case 3:

			GetMesh()->SetAnimInstanceClass(SecondAnimIns);
			GetMesh()->SetSkeletalMesh(SecondSkMesh);

			GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -70.0f));
			GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

			Hp = 400.0f;
			MaxHp = 400.0f;
			GetWorld()->GetTimerManager().SetTimer(EvolutionTimer, this, &AWolfCharacter::SetAmount, 0.01f, true);
			break;

		case 4:
			SecondMeshComponent->SetRelativeScale3D(FVector(1.3f, 1.3f, 1.3f));
			Hp = 450.0f;
			MaxHp = 450.0f;
			GetWorld()->GetTimerManager().SetTimer(EvolutionTimer, this, &AWolfCharacter::SetAmount, 0.01f, true);

			break;

		case 5:
			GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
			GetMesh()->SetSkeletalMesh(ThirdMesh);

			Hp = 500.0f;
			MaxHp = 500.0f;
			GetWorld()->GetTimerManager().SetTimer(EvolutionTimer, this, &AWolfCharacter::SetAmount, 0.01f, true);
			break;
		}
	}
}

void AWolfCharacter::SetAmount()
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


				Hp = 300.0f;
				MaxHp = 300.0f;
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

				Hp = 350.0f;
				MaxHp = 350.0f;
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

				Hp = 400.0f;
				MaxHp = 400.0f;

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

				Hp = 450.0f;
				MaxHp = 450.0f;

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

				Hp = 500.0f;
				MaxHp = 500.0f;
				GetWorld()->GetTimerManager().ClearTimer(EvolutionTimer);
			}

			break;
	}

	

}
