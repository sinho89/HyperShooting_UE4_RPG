// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HSCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class HSPROJECT_API UHSCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UHSCharacterAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	bool GetMoveState() { return _isMoving; }
	bool GetAttackState() { return _isAttacking; }
	bool GetStartAnimPlay() { return _isStartPlay; }

private:
	UFUNCTION()
	void AnimNotify_StartPlay();

	UFUNCTION()
	void AnimNotify_Fire();

	UPROPERTY()
	class AHSCharacterBase* _player;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool _isMoving;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool _isAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool _isStartPlay;
	
};
