// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HSActorBase.generated.h"

UCLASS()
class HSPROJECT_API AHSActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AHSActorBase();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	void SpawnTowerBullet();

public:
	UFUNCTION()
	UHSStatComponent* GetStatComponent() { return _statComponent; }

	UFUNCTION()
	AHSEnemy* GetTarget() { return _target; }
	void SetTarget(AHSEnemy* Target) { _target = Target; }

	void DeleteTarget() { _target = nullptr; }


private:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* _staticMesh;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* _trigger;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* _towerEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	class UHSStatComponent* _statComponent;

	UPROPERTY()
	FTimerHandle _bulletFireTimerHandle;

	UPROPERTY()
	class AHSEnemy* _target;

	UPROPERTY()
	int32 _actorType = 0;
};
