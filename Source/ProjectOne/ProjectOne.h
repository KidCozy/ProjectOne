// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "Engine.h"

#include "Player/ProjectOneCharacter.h"


DECLARE_LOG_CATEGORY_EXTERN(ProjectOne, Log, All);
#define ABCHECK(Expr, ...) {if(!(Expr)) { return __VA_ARGS__;}}
#define ABLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define ABLOG_S(Verbosity) UE_LOG(ProjectOne, Verbosity, TEXT("%s"), *ABLOG_CALLINFO)
#define ABLOG(Verbosity, Format, ...) UE_LOG(ProjectOne, Verbosity, TEXT("%s %s"), *ABLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))