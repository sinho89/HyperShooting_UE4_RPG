#include "HSStatComponent.h"
#include "HSGameInstance.h"
#include "Kismet/GameplayStatics.h"

UHSStatComponent::UHSStatComponent()
	:_level(1)
	, _index(1)
	, _attack(0)
	, _hp(0)
	, _exp(0)
	, _expPoint(0)
{

	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

}

void UHSStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHSStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (_actorType == 0)
		SetPlayerLevel(_level);
	if (_actorType == 1)
		SetMonsterInfo(_index);
	if (_actorType == 2)
		SetTowerLevel(_level);
}

void UHSStatComponent::SetPlayerLevel(int32 Level)
{
	auto gameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (gameInstance)
	{
		auto statData = gameInstance->GetPlayerStatData(Level);

		if (statData)
		{
			_level = statData->Level;
			_maxHp = statData->MaxHp;
			SetHp(_maxHp);
			_attack = statData->Attack;
		}
	}
}

void UHSStatComponent::SetMonsterInfo(int32 Index)
{
	auto gameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (gameInstance)
	{
		auto statData = gameInstance->GetMonsterStatData(Index);

		if (statData)
		{
			_index = statData->Index;
			_maxHp = statData->MaxHp;
			SetHp(_maxHp);
			_attack = statData->Attack;
			_expPoint = statData->ExpPoint;
		}
	}
}

void UHSStatComponent::SetTowerLevel(int32 Level)
{
	auto gameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (gameInstance)
	{
		auto statData = gameInstance->GetTowerStatData(Level);

		if (statData)
		{
			_level = statData->Level;
			_maxHp = statData->MaxHp;
			SetHp(_maxHp);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("SetTowerLevel"));
}

void UHSStatComponent::OnAttacked(int32 DamageValue)
{
	int Hp = _hp - DamageValue;
	SetHp(Hp);
}

void UHSStatComponent::SetHp(int32 Hp)
{
	_hp = Hp;

	if (_hp <= 0)
	{
		OnDead.Broadcast();
		_hp = 0;
	}

	OnHpChanged.Broadcast();
}

