// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HSPlayer.h"
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

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	UUserWidget* GetMainGameWidget();
	AHSPlayer* GetMainGameCharacter() { return _mainGameCharacter; }

private:
	void SpawnMonster();
	void InitializeObjectCreate();
	void SetMainGameCharacter();

public:
	UPROPERTY()
	AHSPlayer* _mainGameCharacter;
	UPROPERTY()
	TSubclassOf<UUserWidget> _HUD_Class;
	UPROPERTY()
	UUserWidget* _mainGameWidget;
	UPROPERTY()
	FTimerHandle _monsterSpawnTimerHandle;

};
