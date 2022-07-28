// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HSMonsterBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEnd);

UCLASS()
class HSPROJECT_API AHSMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHSMonsterBase();

	bool GetMovingState() { return _isMoving; }
	void SetMovingState(bool isMove) { _isMoving = isMove; }

	bool GetAttackingState() { return _isAttacking; }
	void SetAttackingState(bool isAttacking) { _isAttacking = isAttacking; }

	FOnAttackEnd OnAttackEnd;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	class UHSCharacterAnimInstance* _animInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool _isMoving = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool _isAttacking = false;
};
