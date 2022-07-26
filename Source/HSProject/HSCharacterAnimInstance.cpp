// Fill out your copyright notice in the Description page of Project Settings.


#include "HSCharacterAnimInstance.h"
#include "HSCharacterBase.h"
#include "HSBulletBase.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include <Particles/ParticleSystemComponent.h>
#include <Components/BoxComponent.h>

UHSCharacterAnimInstance::UHSCharacterAnimInstance()
{
	_isMoving = false;
	_isAttacking = false;
	_isStartPlay = false;
}

void UHSCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	_player = Cast<AHSCharacterBase>(TryGetPawnOwner());

	if (IsValid(_player))
	{
		_isMoving = _player->GetMovingState();
		_isAttacking = _player->GetAttackingState();
	}
}

void UHSCharacterAnimInstance::AnimNotify_StartPlay()
{
	_isStartPlay = true;

	_player = Cast<AHSCharacterBase>(TryGetPawnOwner());

	if (IsValid(_player))
		_player->SetPlayStart(true);
}

void UHSCharacterAnimInstance::AnimNotify_Fire()
{
	if (IsValid(_player))
	{
		if (!_isAttacking)
			return;

		FName muzzleSocket(TEXT("Muzzle_01"));
		GetWorld()->SpawnActor<AHSBulletBase>(_player->GetMesh()->GetSocketLocation(muzzleSocket), _player->GetBulletRotation());
	}
}
