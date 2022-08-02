// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HSPlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class HSPROJECT_API AHSPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	AHSPlayerControllerBase();

protected:
	virtual void BeginPlayingState() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

private:

	UPROPERTY()
	class AHSPlayer* _player;

	UPROPERTY()
	bool _isMoveClick;

	UPROPERTY()
	FVector _moveToPos;

	UPROPERTY()
	float _moveDistance;

	UPROPERTY()
	bool _isAttackClick;

	UPROPERTY()
	FVector _attackToPos;

	UPROPERTY()
	bool _isStartPlay;


	
	void Moving();
	void MoveToMouseCursor();
	void SetNewMoveDestination(const FVector DestLocation);
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
	void CancleMove();

	void Attacking();
	void AttackToMouseCursor();
	void SetAttacking(const FVector DestLocation);
	void OnAttackPressed();
	void OnAttackReleased();
	void CancleAttack();

	void GameStartCheck();
	
};
