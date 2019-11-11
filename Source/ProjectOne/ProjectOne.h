// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "Engine.h"

UENUM(BlueprintType)
enum class E_PlayerSelect : uint8
{
	E_SMG = 1 UMETA(DisplayName = "SubMachinGun"),
	E_LAUNCHER = 8 UMETA(DisplayName = "Launcher"),
	E_RF = 15 UMETA(DisplayName = "Rifle")
};

UENUM(BlueprintType)
enum class E_Item : uint8
{
	E_NONE UMETA(DisplayName = "None"),
	E_RESURRECTION UMETA(DisplayName = "resurrection"),
	E_FIRE_GRANEDE UMETA(DisplayName = "FireGranade"),
	E_SMOKE_GRANADE UMETA(DisplayName = "SmokeGranade"),
	E_EVOLUTION UMETA(DisplayName = "Evolution"),
	E_SHEILD UMETA(DisplayName = "Sheild"),
	E_SUCKSANG UMETA(DisplayName = "SuckSang"),
	E_AP_BUFF UMETA(DisplayName = "APBuff"),
	E_AP_DEBUFF_BULLET UMETA(DisplayName = "APDeBuffBullet"),
	E_SPEED_BUFF UMETA(DisplayName = "SpeedBuff"),
	E_SPEED_DEBUFF_BULLET UMETA(DisplayName = "SpeedDebuffBullet"),
	E_HEAL_50 UMETA(DisplayName = "Heal50"),
	E_HEAL_100 UMETA(DisplayName = "Heal100"),
	E_HEAL_150 UMETA(DisplayName = "Heal150")
};


DECLARE_LOG_CATEGORY_EXTERN(ProjectOne, Log, All);
#define ABCHECK(Expr, ...) {if(!(Expr)) { return __VA_ARGS__;}}
#define ABLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define ABLOG_S(Verbosity) UE_LOG(ProjectOne, Verbosity, TEXT("%s"), *ABLOG_CALLINFO)
#define ABLOG(Verbosity, Format, ...) UE_LOG(ProjectOne, Verbosity, TEXT("%s %s"), *ABLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))