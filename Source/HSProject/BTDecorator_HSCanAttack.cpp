// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_HSCanAttack.h"
#include "HSAIController.h"
#include "HSActorBase.h"
#include "HSCharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_HSCanAttack::UBTDecorator_HSCanAttack()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_HSCanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto currentPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (currentPawn == nullptr)
		return false;

	auto target = Cast<AHSActorBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));

	if (target == nullptr)
		return false;

	auto pawn = Cast<AHSCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());

	if (target->GetDistanceTo(currentPawn) <= 200.f)
	{
		pawn->SetAttackingState(true);
		pawn->SetMovingState(false);
		return true;
	}
	else
	{
		pawn->SetAttackingState(false);
		pawn->SetMovingState(true);
		return false;
	}

	return result;
}
