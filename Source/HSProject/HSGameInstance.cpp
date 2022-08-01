#include "HSGameInstance.h"
#include "HSActorBase.h"
#include <Serialization/JsonReader.h>
#include <Templates/SharedPointer.h>
#include "HSCharacterBase.h"
#include "DrawDebugHelpers.h"

UHSGameInstance::UHSGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> PD(TEXT("DataTable'/Game/Data/PlayerStatsData.PlayerStatsData'"));
	_playerStats = PD.Object;
	static ConstructorHelpers::FObjectFinder<UDataTable> MD(TEXT("DataTable'/Game/Data/MonsterStatsData.MonsterStatsData'"));
	_monsterStats = MD.Object;
	static ConstructorHelpers::FObjectFinder<UDataTable> TD(TEXT("DataTable'/Game/Data/TowerStatsData.TowerStatsData'"));
	_towerStats = TD.Object;

	_towerActor = NULL;
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

void UHSGameInstance::CreateTower()
{
	_towerActor = GetWorld()->SpawnActor<AHSActorBase>();
}

void UHSGameInstance::CreateLeftMonster()
{
	FName path = TEXT("Class'/Game/BluePrints/BP_Monster0.BP_Monster0_C'");

	FVector spawnLocation = FVector(1160.f, -1180.f, 200.f);
	FVector const spawnDir = FVector::ZeroVector - spawnLocation;
	FRotator spawnRotator = FRotator(0.f, spawnDir.Rotation().Yaw, 0.f);

	UClass* generatedBP = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *path.ToString()));

	if (generatedBP)
		GetWorld()->SpawnActor<AHSCharacterBase>(generatedBP, spawnLocation, spawnRotator);
}

void UHSGameInstance::CreateRightMonster()
{
	FName path = TEXT("Class'/Game/BluePrints/BP_Monster0.BP_Monster0_C'");

	FVector spawnLocation = FVector(1460, 780.f, 200.f);
	FVector const spawnDir = FVector::ZeroVector - spawnLocation;
	FRotator spawnRotator = FRotator(0.f, spawnDir.Rotation().Yaw, 0.f);

	UClass* generatedBP = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *path.ToString()));
	if (generatedBP)
		GetWorld()->SpawnActor<AHSCharacterBase>(generatedBP, spawnLocation, spawnRotator);
}
