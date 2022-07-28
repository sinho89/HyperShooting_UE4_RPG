// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_HSAttack.generated.h"

/**
 * 
 */
UCLASS()
class HSPROJECT_API UBTTask_HSAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_HSAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

private:
	bool _isAttacking = false;

};
