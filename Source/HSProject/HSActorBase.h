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
	virtual void PostInitializeComponents() override;

private:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* _staticMesh;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* _trigger;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* _towerEffect;

	UPROPERTY(VisibleAnywhere)
	class UHSStatComponent* _statComponent;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* _widgetComponent;

	UPROPERTY()
	int32 _actorType = 0;
};
