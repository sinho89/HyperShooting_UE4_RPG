// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HSCharacterBase.h"
#include "HSEnemy.generated.h"

/**
 * 
 */
UCLASS()
class HSPROJECT_API AHSEnemy : public AHSCharacterBase
{
	GENERATED_BODY()

public:
	AHSEnemy();

	void SetUniqueId(int32 Id) { _uniqueID = Id; }

protected:
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void SetAnimComponent() override;
	virtual void SetStatComponent() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* _worldHpWidgetComponent;

	int32 _uniqueID;
};
