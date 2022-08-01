#include "BTTask_HSResetIdle.h"
#include "HSCharacterBase.h"
#include "HSAIController.h"
#include "HSEnemy.h"

UBTTask_HSResetIdle::UBTTask_HSResetIdle()
{
	NodeName = TEXT("ResetIdle");
}

EBTNodeResult::Type UBTTask_HSResetIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Cast<AHSMonsterBase>(OwnerComp.GetAIOwner()->GetPawn())->SetMovingState(false);
	Cast<AHSEnemy>(OwnerComp.GetAIOwner()->GetPawn())->SetMovingState(false);
	Cast<AHSEnemy>(OwnerComp.GetAIOwner()->GetPawn())->SetAttackingState(false);
	return EBTNodeResult::Succeeded;
}
