// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_HSAttack.h"
#include "HSAIController.h"
#include "HSCharacterBase.h"
#include "HSEnemy.h"

UBTTask_HSAttack::UBTTask_HSAttack()
{
	bNotifyTick = true;
	_isAttacking = false;
}

EBTNodeResult::Type UBTTask_HSAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	//auto monster = Cast<AHSMonsterBase>(OwnerComp.GetAIOwner()->GetPawn());
	auto _pawn = Cast<AHSEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	
	if (_pawn == nullptr)
		return EBTNodeResult::Failed;

	_pawn->SetAttackingState(true);
	_isAttacking = true;

	_pawn->OnAttackEnd.AddLambda([this]()
		{ 
			_isAttacking = false;
		});

	return result;
}

void UBTTask_HSAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (_isAttacking == false)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		auto _pawn = Cast<AHSEnemy>(OwnerComp.GetAIOwner()->GetPawn());
		_pawn->SetAttackingState(false);
	}

}
