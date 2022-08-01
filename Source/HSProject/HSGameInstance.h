// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "HSCharacterBase.h"
#include "HSGameInstance.generated.h"

/**
 * 
 */
USTRUCT()
struct FPlayerStatData : public FTableRowBase
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxExp;
};

USTRUCT()
struct FMonsterStatData : public FTableRowBase
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ExpPoint;
};

USTRUCT()
struct FTowerStatData : public FTableRowBase
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MaxHp;
};

UCLASS()
class HSPROJECT_API UHSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UHSGameInstance();

	virtual void Init() override;

	FPlayerStatData* GetPlayerStatData(int32 Level);
	FMonsterStatData* GetMonsterStatData(int32 Index);
	FTowerStatData* GetTowerStatData(int32 Level);

	void CreateTower();
	void CreateLeftMonster();
	void CreateRightMonster();

	UFUNCTION()
	AHSActorBase* GetTowerActor() { return _towerActor; }
private:
	UPROPERTY()
	class UDataTable* _playerStats;

	UPROPERTY()
	class UDataTable* _monsterStats;

	UPROPERTY()
	class UDataTable* _towerStats;


	UPROPERTY()
	AHSActorBase* _towerActor;

	UPROPERTY()
	TMap<int32, AHSCharacterBase*> _objectMap;
};
