// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HSStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDead);
DECLARE_MULTICAST_DELEGATE(FOnHpChanged);
DECLARE_MULTICAST_DELEGATE(FOnExpChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HSPROJECT_API UHSStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHSStatComponent();

protected:
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:

	void SetPlayerLevel(int32 Level);
	void SetMonsterInfo(int32 Index);
	void SetTowerLevel(int32 Level);

	void OnAttacked(int32 DamageValue);
	void OnGetExp(int32 ExpValue);

	void SetHp(int32 Hp);
	void SetExp(int32 Exp);

	float GetHpRatio() { return _hp / (float)_maxHp; }
	float GetExpRatio() { return _exp / (float)_maxExp; }

	int32 GetLevel() { return _level; }
	int32 GetIndex() { return _index; }
	int32 GetAttack() { return _attack; }
	int32 GetHp() { return _hp; }
	int32 GetMaxHp() { return _maxHp; }
	int32 GetExp() { return _exp; }
	int32 GetMaxExp() { return _maxExp; }
	int32 GetExpPoint() { return _expPoint; }

	FOnDead OnDead;
	FOnHpChanged OnHpChanged;
	FOnExpChanged OnExpChanged;

private:
	UPROPERTY(EditAnywhere, Category=Stat, Meta=(AllowPrivateAccess=true))
		int32 _level;
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 _index;
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 _attack;
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 _hp;
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 _maxHp;
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 _exp;
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 _maxExp;
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 _expPoint;
};
