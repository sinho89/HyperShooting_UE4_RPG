#include "BTTask_HSResetIdle.h"
#include "HSCharacterBase.h"
#include "HSAIController.h"

UBTTask_HSResetIdle::UBTTask_HSResetIdle()
{
	NodeName = TEXT("ResetIdle");
}

EBTNodeResult::Type UBTTask_HSResetIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Cast<AHSMonsterBase>(OwnerComp.GetAIOwner()->GetPawn())->SetMovingState(false);
	Cast<AHSCharacterBase>(OwnerComp.GetAIOwner()->GetPawn())->SetMovingState(false);
	Cast<AHSCharacterBase>(OwnerComp.GetAIOwner()->GetPawn())->SetAttackingState(false);
	return EBTNodeResult::Succeeded;
}