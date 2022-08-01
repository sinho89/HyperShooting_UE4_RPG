// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HSCharacterBase.h"
#include "HSPlayer.generated.h"

/**
 * 
 */
UCLASS()
class HSPROJECT_API AHSPlayer : public AHSCharacterBase
{
	GENERATED_BODY()

public:
	AHSPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void SetAnimComponent() override;
	virtual void SetStatComponent() override;
public:
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return _cameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return _springArmComponent; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* _cameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* _springArmComponent;
};
