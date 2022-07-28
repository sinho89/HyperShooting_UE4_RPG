// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HSProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class HSPROJECT_API AHSProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AHSProjectGameModeBase();

public:
	UPROPERTY()
	TSubclassOf<UUserWidget> _HUD_Class;

	UPROPERTY()
	UUserWidget* _currentWidget;

};
