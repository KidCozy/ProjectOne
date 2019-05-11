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

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MANEQUIN(TEXT("SkeletalMesh'/Game/Animations/Exper/Mesh/SK_Wolf1_Idle_dog0F.SK_Wolf1_Idle_dog0F'"));
	if (SK_MANEQUIN.Succeeded())
		GetMesh()->SetSkeletalMesh(SK_MANEQUIN.Object);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -42.0f), FRotator(0.0f, -90.0f, 0.0f));
	
	static ConstructorHelpers::FClassFinder<UAnimInstance> TEMP_ANIM(TEXT("AnimBlueprint'/Game/Animations/Exper/Wolf1_AnimBP.Wolf1_AnimBP_C'"));
	if (TEMP_ANIM.Succeeded())
		GetMesh()->SetAnimInstanceClass(TEMP_ANIM.Class);

	

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Sec(TEXT("SkeletalMesh'/Game/Animations/Wolf2Build/SK_Wolf2_Idle.SK_Wolf2_Idle'"));
	if (SK_Sec.Succeeded()) {
		SecondSkMesh = SK_Sec.Object;
		SecondMeshComponent->SetSkeletalMesh(SecondSkMesh);
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

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> EVOLUTION_START_MATERIAL(TEXT("MaterialInstanceConstant'/Game/Animations/Exper/Mesh/Barrier_Invert_Micro_Inst.Barrier_Invert_Micro_Inst'"));
	if (EVOLUTION_START_MATERIAL.Succeeded())
	{

		GetMesh()->SetMaterial(0, EVOLUTION_START_MATERIAL.Object);

		Mat.Add(GetMesh()->GetMaterial(0));

		DynamicShader.Add(GetMesh()->CreateDynamicMaterialInstance(0, Mat[0]));

		GetMesh()->SetMaterial(0, DynamicShader[0]);

		DynamicShader[0]->SetScalarParameterValue("Amount", 0.0f);
		DynamicShader[0]->SetScalarParameterValue("EmissiveAmount", 150.0f);
		DynamicShader[0]->SetScalarParameterValue("Fringe", 40.0f);
		DynamicShader[0]->SetScalarParameterValue("Offset", 3.5f);
		DynamicShader[0]->SetScalarParameterValue("TransitionTime", 3.0f);

		DynamicShader[0]->SetVectorParameterValue("GlowColor", FLinearColor::FLinearColor(0.2f, 0.3f, 0.8f));
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> EVOLUTION_END_MATERIAL(TEXT("MaterialInstanceConstant'/Game/Animations/Wolf2Build/Material/Barrier_Invert_Micro_2_Inst.Barrier_Invert_Micro_2_Inst'"));
	if (EVOLUTION_END_MATERIAL.Succeeded()) {

		SecondMeshComponent->SetMaterial(0, EVOLUTION_END_MATERIAL.Object);

		Mat.Add(SecondMeshComponent->GetMaterial(0));

		DynamicShader.Add(SecondMeshComponent->CreateDynamicMaterialInstance(0, Mat[1]));

		SecondMeshComponent->SetMaterial(0, DynamicShader[1]);


		DynamicShader[1]->SetScalarParameterValue("Amount", 0.5f);
		DynamicShader[1]->SetScalarParameterValue("EmissiveAmount", 150.0f);
		DynamicShader[1]->SetScalarParameterValue("Fringe", 40.0f);
		DynamicShader[1]->SetScalarParameterValue("Offset", 3.5f);
		DynamicShader[1]->SetScalarParameterValue("TransitionTime", 3.0f);

		DynamicShader[1]->SetVectorParameterValue("GlowColor", FLinearColor::FLinearColor(0.2f, 0.3f, 0.8f));
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> EVOLUTION_THIRDDOWN_MATERIAL(TEXT("MaterialInstanceConstant'/Game/Animations/Wolf3Build/Material/M_Wolf3EvolutionMat_Down_Inst.M_Wolf3EvolutionMat_Down_Inst'"));
	if (EVOLUTION_THIRDDOWN_MATERIAL.Succeeded())
	{

		GetMesh()->SetMaterial(1, EVOLUTION_THIRDDOWN_MATERIAL.Object);

		Mat.Add(GetMesh()->GetMaterial(1));

		DynamicShader.Add(GetMesh()->CreateDynamicMaterialInstance(1, Mat[2]));

		GetMesh()->SetMaterial(1, DynamicShader[2]);

		DynamicShader[2]->SetScalarParameterValue("Amount", 0.6f);
		DynamicShader[2]->SetScalarParameterValue("EmissiveAmount", 150.0f);
		DynamicShader[2]->SetScalarParameterValue("Fringe", 40.0f);
		DynamicShader[2]->SetScalarParameterValue("Offset", 3.5f);
		DynamicShader[2]->SetScalarParameterValue("TransitionTime", 3.0f);

		DynamicShader[2]->SetVectorParameterValue("GlowColor", FLinearColor::FLinearColor(0.2f, 0.3f, 0.8f));
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> EVOLUTION_THIRDUP_MATERIAL(TEXT("MaterialInstanceConstant'/Game/Animations/Wolf3Build/Material/M_Wolf3EvolutionMat_Up_Inst.M_Wolf3EvolutionMat_Up_Inst'"));
	if (EVOLUTION_THIRDUP_MATERIAL.Succeeded()) {

		GetMesh()->SetMaterial(2, EVOLUTION_THIRDUP_MATERIAL.Object);

		Mat.Add(GetMesh()->GetMaterial(2));

		DynamicShader.Add(GetMesh()->CreateDynamicMaterialInstance(2, Mat[3]));

		GetMesh()->SetMaterial(2, DynamicShader[3]);

		DynamicShader[3]->SetScalarParameterValue("Amount", 0.6f);
		DynamicShader[3]->SetScalarParameterValue("EmissiveAmount", 150.0f);
		DynamicShader[3]->SetScalarParameterValue("Fringe", 40.0f);
		DynamicShader[3]->SetScalarParameterValue("Offset", 3.5f);
		DynamicShader[3]->SetScalarParameterValue("TransitionTime", 3.0f);

		DynamicShader[3]->SetVectorParameterValue("GlowColor", FLinearColor::FLinearColor(0.2f, 0.3f, 0.8f));
	}


	
	SetActorScale3D(FVector(0.7f,0.7f,0.7f));
}

void AWolfCharacter::Evolution() {
	if (IsAlive) {
		switch (CurLevel) {
		case 0:
			SecondMeshComponent->SetVisibility(true);
			/* 여기에 변화하는 코드 추가 */
			SecondMeshComponent->SetAnimInstanceClass(SecondAnimIns);

			APAnim = Cast<UPlayerCharacterAnimInstance>(SecondMeshComponent->GetAnimInstance());
			GetCapsuleComponent()->SetCapsuleSize(35.0f, 70.0f);

			SecondMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -70.0f));
			SecondMeshComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

			CameraBoom->SocketOffset = FVector(100.0f, 50.0f, 90.0f);
			SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
			
			/*종료되면 첫번째 스켈레탈 메쉬는 가리고 세 번째 메쉬를 로드시킴*/
			GetWorld()->GetTimerManager().SetTimer(EvolutionTimer, this, &AWolfCharacter::SetAmount, 0.01f, true);
			break;
		case 1:
			GetMesh()->SetVisibility(true);

			SecondMeshComponent->SetAnimInstanceClass(SecondAnimIns);
			APAnim = Cast<UPlayerCharacterAnimInstance>(SecondMeshComponent->GetAnimInstance());

			SecondMeshComponent->SetVisibility(true);

			GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -70.0f));
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
				SetScalarParameter(SecondMeshComponent, 0, 0, SecCurAmount);
			}
			else {
				APAnim->Evolution();
	
				++CurLevel;
	
				GetWorld()->GetTimerManager().ClearTimer(EvolutionTimer);
				GetMesh()->SetSkeletalMesh(ThirdMesh);
				GetMesh()->SetAnimInstanceClass(ThirdAnimIns);

				GetMesh()->SetMaterial(0, GetMesh()->GetMaterial(1));
				GetMesh()->SetMaterial(1, GetMesh()->GetMaterial(2));

				Weapone->IntervalTime = 0.06f;

				curAmount = 0.6;
				Hp = 100.0f;
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
				SetScalarParameter(SecondMeshComponent, 0, 0, SecCurAmount);
			}
			else {
				APAnim->Evolution();

				++CurLevel;


				GetWorld()->GetTimerManager().ClearTimer(EvolutionTimer);
				GetMesh()->SetSkeletalMesh(ThirdMesh);
				Weapone->IntervalTime = 0.06f;
				Hp = 100.0f;
			}
			break;
	
	}

	

}
