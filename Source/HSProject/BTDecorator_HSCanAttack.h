// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_HSCanAttack.generated.h"

/**
 * 
 */
UCLASS()
class HSPROJECT_API UBTDecorator_HSCanAttack : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_HSCanAttack();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
