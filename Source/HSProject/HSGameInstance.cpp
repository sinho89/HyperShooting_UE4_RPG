#include "HSGameInstance.h"
#include "HSActorBase.h"
#include <Serialization/JsonReader.h>
#include <Templates/SharedPointer.h>
#include "HSPlayer.h"
#include "DrawDebugHelpers.h"
#include "HSStatComponent.h"
#include "HSEnemy.h"

UHSGameInstance::UHSGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> PD(TEXT("DataTable'/Game/Data/PlayerStatsData.PlayerStatsData'"));
	_playerStats = PD.Object;
	static ConstructorHelpers::FObjectFinder<UDataTable> MD(TEXT("DataTable'/Game/Data/MonsterStatsData.MonsterStatsData'"));
	_monsterStats = MD.Object;
	static ConstructorHelpers::FObjectFinder<UDataTable> TD(TEXT("DataTable'/Game/Data/TowerStatsData.TowerStatsData'"));
	_towerStats = TD.Object;

	_tower = nullptr;

	_monsterUniqueIndex = 0;
}

void UHSGameInstance::Init()
{
	Super::Init();
}

FPlayerStatData* UHSGameInstance::GetPlayerStatData(int32 Level)
{
	return _playerStats->FindRow<FPlayerStatData>(*FString::FromInt(Level), TEXT(""));
}

FMonsterStatData* UHSGameInstance::GetMonsterStatData(int32 Index)
{
	return _monsterStats->FindRow<FMonsterStatData>(*FString::FromInt(Index), TEXT(""));
}

FTowerStatData* UHSGameInstance::GetTowerStatData(int32 Level)
{
	return _towerStats->FindRow<FTowerStatData>(*FString::FromInt(Level), TEXT(""));
}

AHSEnemy* UHSGameInstance::GetCloserEnemyByTower()
{
	AHSEnemy* resultActor = nullptr;
	FVector startLocation = FVector(0.f, 0.f, 500.f);
	float compareDistance = 3000.f;

	UE_LOG(LogTemp, Error, TEXT("%d"), _enemyMap.Num());

	if (_enemyMap.Num() <= 0)
		return nullptr;

	for (auto& enemy : _enemyMap)
	{
		float distance = (enemy.Value->GetActorLocation() - startLocation).Size();

		if(compareDistance > distance)
			resultActor = enemy.Value;

		compareDistance = distance;
	}

	if (compareDistance >= 3000.f)
		return nullptr;

	_tower->SetTarget(resultActor);

	return resultActor;
}

void UHSGameInstance::CreateTower()
{
	_tower = GetWorld()->SpawnActor<AHSActorBase>();
}

void UHSGameInstance::CreateLeftMonster()
{
	FName path = TEXT("Class'/Game/BluePrints/BP_Monster0.BP_Monster0_C'");

	FVector spawnLocation = FVector(1160.f, -1180.f, 200.f);
	FVector const spawnDir = FVector::ZeroVector - spawnLocation;
	FRotator spawnRotator = FRotator(0.f, spawnDir.Rotation().Yaw, 0.f);

	UClass* generatedBP = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *path.ToString()));

	if (generatedBP)
	{
		auto enemy = GetWorld()->SpawnActor<AHSEnemy>(generatedBP, spawnLocation, spawnRotator);

		if (enemy)
		{
			int32 index = Cast<AHSCharacterBase>(enemy)->GetStatComponent()->GetIndex();
			_enemyMap.Add(_monsterUniqueIndex, enemy);
			enemy->SetUniqueId(_monsterUniqueIndex);
			_monsterUniqueIndex++;
		}
	}
}

void UHSGameInstance::CreateRightMonster()
{
	FName path = TEXT("Class'/Game/BluePrints/BP_Monster0.BP_Monster0_C'");

	FVector spawnLocation = FVector(1460, 780.f, 200.f);
	FVector const spawnDir = FVector::ZeroVector - spawnLocation;
	FRotator spawnRotator = FRotator(0.f, spawnDir.Rotation().Yaw, 0.f);

	UClass* generatedBP = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *path.ToString()));
	
	if (generatedBP)
	{
		auto enemy = GetWorld()->SpawnActor<AHSEnemy>(generatedBP, spawnLocation, spawnRotator);

		if (enemy)
		{
			int32 index = Cast<AHSCharacterBase>(enemy)->GetStatComponent()->GetIndex();
			_enemyMap.Add(_monsterUniqueIndex, enemy);
			enemy->SetUniqueId(_monsterUniqueIndex);
			_monsterUniqueIndex++;
		}
	}
}
