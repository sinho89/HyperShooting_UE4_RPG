// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_HSSearchTarget.h"
#include "HSAIController.h"
#include "HSCharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_HSSearchTarget::UBTService_HSSearchTarget()
{
	NodeName = TEXT("SearchTarget");
	Interval = 1.0f;
}

void UBTService_HSSearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto currentPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (currentPawn == nullptr)
		return;

	UWorld* world = currentPawn->GetWorld();
	FVector center = currentPawn->GetActorLocation();
	float searchRadius = 1000.f;

	if (world == nullptr)
		return;
	
	TArray<FOverlapResult> overlapResults;
	FCollisionQueryParams QueryParams(NAME_None, false, currentPawn);

	bool result = world->OverlapMultiByChannel(overlapResults, center, FQuat::Identity, 
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(searchRadius), QueryParams);

	if (result)
	{
		for (auto& overlapResult : overlapResults)
		{
			AHSCharacterBase* target = Cast<AHSCharacterBase>(overlapResult.GetActor());
			if (target && target->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), target);

				DrawDebugSphere(world, center, searchRadius, 16, FColor::Green, false, 0.2f);
				return;
			}
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);
	}

	DrawDebugSphere(world, center, searchRadius, 16, FColor::Red, false, 0.2f);

}
