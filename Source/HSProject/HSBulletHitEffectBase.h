// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HSBulletHitEffectBase.generated.h"

UCLASS()
class HSPROJECT_API AHSBulletHitEffectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHSBulletHitEffectBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* _hitEffect;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* _trigger;
};
