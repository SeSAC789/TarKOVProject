// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#define GETENUMSTRING(ENUM, ENUMVALUE) (FindObject<UEnum>(ANY_PACKAGE, TEXT(ENUM), true)->GetNameStringByValue((int64)ENUMVALUE)) //로그 출력위해 추가함
