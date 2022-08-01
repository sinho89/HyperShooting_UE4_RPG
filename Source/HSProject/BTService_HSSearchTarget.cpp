// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_HSSearchTarget.h"
#include "HSAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "HSGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include "HSPlayer.h"
#include "HSProjectGameModeBase.h"

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

	auto gameMode = Cast<AHSProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	AHSPlayer* target = Cast<AHSPlayer>(gameMode->GetMainGameCharacter());

	if (target)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), target);
		return;
	}
	
	/*UWorld* world = currentPawn->GetWorld();
	FVector center = currentPawn->GetActorLocation();
	float searchRadius = 5000.f;

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
				return;
			}
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);
	}*/


}
