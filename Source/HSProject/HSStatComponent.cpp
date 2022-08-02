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

	auto ownerActor = GetOwner();
	if (ownerActor->ActorHasTag(TEXT("Player")))
		SetPlayerLevel(_level);
	else if (ownerActor->ActorHasTag(TEXT("Enemy")))
		SetMonsterInfo(_index);
	else if (ownerActor->ActorHasTag(TEXT("Tower")))
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
			_maxExp = statData->MaxExp;
			SetExp(_exp);
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
	UE_LOG(LogTemp, Warning, TEXT("SetMonsterInfo"));
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
			_attack = statData->Attack;
			_maxHp = statData->MaxHp;
			SetHp(_maxHp);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("SetTowerLevel HP:%d"), _maxHp);
}

void UHSStatComponent::OnAttacked(int32 DamageValue)
{
	int Hp = _hp - DamageValue;
	SetHp(Hp);
}

void UHSStatComponent::SetHp(int32 Hp)
{
	_hp = Hp;
	UE_LOG(LogTemp, Warning, TEXT("SetHp HP:%d"), _hp);

	if (_hp <= 0)
	{
		OnDead.Broadcast();
		_hp = 0;
	}

	OnHpChanged.Broadcast();
}

void UHSStatComponent::OnGetExp(int32 ExpValue)
{
	_exp += ExpValue;
	SetExp(_exp);
}

void UHSStatComponent::SetExp(int32 Exp)
{
	_exp = Exp;

	if (_exp >= _maxExp)
	{
		_exp = 0;
		UE_LOG(LogTemp, Error, TEXT("Level Up"));
		_level++;

		SetPlayerLevel(_level);
	}

	OnExpChanged.Broadcast();
}

