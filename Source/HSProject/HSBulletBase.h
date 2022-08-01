// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HSBulletBase.generated.h"

UCLASS()
class HSPROJECT_API AHSBulletBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AHSBulletBase();

protected:
	virtual void PostInitializeComponents() override;

public:
	UFUNCTION()
	void SetBulletOwner(AHSCharacterBase* BulletOwner) { _bulletOwner = BulletOwner; }

private:
	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* _bulletEffect;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* _trigger;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* _moveComponent;

	UPROPERTY(VisibleAnywhere)
	AHSCharacterBase* _bulletOwner;
};
