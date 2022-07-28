// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_HSResetIdle.generated.h"

/**
 * 
 */
UCLASS()
class HSPROJECT_API UBTTask_HSResetIdle : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_HSResetIdle();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
