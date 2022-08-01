// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HSCharacterBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEnd);

UCLASS()
class HSPROJECT_API AHSCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AHSCharacterBase();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void SetAnimComponent();
	virtual void SetStatComponent();

public:

	bool GetMovingState() { return _isMoving; }
	void SetMovingState(bool isMove) { _isMoving = isMove; }

	bool GetAttackingState() { return _isAttacking; }
	void SetAttackingState(bool isAttacking) { _isAttacking = isAttacking; }

	bool GetDeadState() { return _isDead; }
	void SetDeadState(bool isDead) { _isDead = isDead; }

	bool GetPlayStart() { return _isStartPlay; }
	void SetPlayStart(bool isStartPlay) { _isStartPlay = isStartPlay; }

	FRotator GetBulletRotation() { return _bulletRotation; }
	void SetBulletRotation(FRotator bulletRotation) { _bulletRotation = bulletRotation; }

	UFUNCTION()
	UHSStatComponent* GetStatComponent() { return _statComponent; }

	FOnAttackEnd OnAttackEnd;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	class UHSCharacterAnimInstance* _animInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	class UHSStatComponent* _statComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool _isMoving = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool _isAttacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool _isStartPlay = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool _isDead = false;

	UPROPERTY()
	FRotator _bulletRotation;
};
