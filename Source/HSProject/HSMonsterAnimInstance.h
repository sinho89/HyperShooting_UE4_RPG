// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HSMonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class HSPROJECT_API UHSMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UHSMonsterAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	bool GetMoveState() { return _isMoving; }
	bool GetAttackState() { return _isAttacking; }
	bool GetStartAnimPlay() { return _isStartPlay; }

private:

	UPROPERTY()
		class AHSMonsterBase* _monster;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool _isMoving;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool _isAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool _isStartPlay;
	
};
