#include "BTTask_HSFindPatrolPos.h"
#include "HSAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "HSMonsterBase.h"

UBTTask_HSFindPatrolPos::UBTTask_HSFindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTask_HSFindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto currentPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (currentPawn == nullptr)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (navSystem == nullptr)
		return EBTNodeResult::Failed;

	FNavLocation randomLocation;

	if (navSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.f, randomLocation))
	{
		//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, randomLocation);
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("PatrolPos")), randomLocation.Location);
		Cast<AHSMonsterBase>(currentPawn)->SetMovingState(true);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
