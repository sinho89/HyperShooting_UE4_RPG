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

	virtual void InitGameState() override;

private:
	void SpawnMonster();
	void InitializeMainUI();
	void InitializeObjectCreate();

public:
	UPROPERTY()
	TSubclassOf<UUserWidget> _HUD_Class;

	UPROPERTY()
	class UUserWidget* _currentWidget;

	UPROPERTY()
	class UHSHUD* _mainUIWidget;

	UPROPERTY()
	FTimerHandle _leftMonsterSpawnTimerHandle;
	
	UPROPERTY()
	FTimerHandle _rightMonsterSpawnTimerHandle;

};
