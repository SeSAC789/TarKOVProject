// Copyright Epic Games, Inc. All Rights Reserved.

#include "TarKOVProject.h"
#include "Modules/ModuleManager.h"
#define GETENUMSTRING(ENUM, ENUMVALUE) (FindObject<UEnum>(ANY_PACKAGE, TEXT(ENUM), true)->GetNameStringByValue((int64)ENUMVALUE))// 로그 출력 위해 추가함

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, TarKOVProject, "TarKOVProject" );
 