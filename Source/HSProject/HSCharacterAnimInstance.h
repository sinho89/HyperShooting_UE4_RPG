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
	bool GetDeadState() { return _isDead; }
	bool GetStartAnimPlay() { return _isStartPlay; }

private:
	UFUNCTION()
	void AnimNotify_StartPlay();
	UFUNCTION()
	void AnimNotify_Fire();
	UFUNCTION()
	void AnimNotify_LeftPlant();
	UFUNCTION()
	void AnimNotify_RightPlant();
	UFUNCTION()
	void AnimNotify_AttackHit();
	UFUNCTION()
	void AnimNotify_AttackEnd();
	UFUNCTION()
	void AnimNotify_DeadEnd();


	UPROPERTY()
	class AHSCharacterBase* _character;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool _isMoving;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool _isAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool _isStartPlay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool _isDead;
	
};
