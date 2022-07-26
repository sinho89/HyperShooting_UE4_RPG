// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HSAIController.generated.h"

/**
 * 
 */
UCLASS()
class HSPROJECT_API AHSAIController : public AAIController
{
	GENERATED_BODY()

public:
	AHSAIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	void RandomMove();

private:
	FTimerHandle _timerHandle;

	UPROPERTY()
	class UBehaviorTree* _behaviorTree;

	UPROPERTY()
	class UBlackboardData* _blackboardData;
};
