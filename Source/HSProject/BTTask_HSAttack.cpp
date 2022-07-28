// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_HSAttack.h"
#include "HSAIController.h"
#include "HSMonsterBase.h"

UBTTask_HSAttack::UBTTask_HSAttack()
{
	bNotifyTick = true;
	_isAttacking = false;
}

EBTNodeResult::Type UBTTask_HSAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto monster = Cast<AHSMonsterBase>(OwnerComp.GetAIOwner()->GetPawn());

	if (monster == nullptr)
		return EBTNodeResult::Failed;

	monster->SetAttackingState(true);
	_isAttacking = true;

	monster->OnAttackEnd.AddLambda([this]()
		{ 
			_isAttacking = false;
		});

	if (!_isAttacking)
		monster->SetAttackingState(false);

	return result;
}

void UBTTask_HSAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (_isAttacking == false)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);


}
