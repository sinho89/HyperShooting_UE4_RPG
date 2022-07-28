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

public:

	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return _cameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return _springArmComponent; }

	bool GetMovingState() { return _isMoving; }
	void SetMovingState(bool isMove) { _isMoving = isMove; }

	bool GetAttackingState() { return _isAttacking; }
	void SetAttackingState(bool isAttacking) { _isAttacking = isAttacking; }

	bool GetPlayStart() { return _isStartPlay; }
	void SetPlayStart(bool isStartPlay) { _isStartPlay = isStartPlay; }

	FRotator GetBulletRotation() { return _bulletRotation; }
	void SetBulletRotation(FRotator bulletRotation) { _bulletRotation = bulletRotation; }

	FOnAttackEnd OnAttackEnd;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* _cameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* _springArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	class UHSCharacterAnimInstance* _animInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool _isMoving = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool _isAttacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool _isStartPlay = false;

	UPROPERTY()
	FRotator _bulletRotation;
};
