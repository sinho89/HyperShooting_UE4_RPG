// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_HSFindPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class HSPROJECT_API UBTTask_HSFindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_HSFindPatrolPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
