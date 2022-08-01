// Fill out your copyright notice in the Description page of Project Settings.


#include "HSCharacterAnimInstance.h"
#include "HSCharacterBase.h"
#include "HSBulletBase.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include <Particles/ParticleSystemComponent.h>
#include <Components/BoxComponent.h>
#include "HSStatComponent.h"

UHSCharacterAnimInstance::UHSCharacterAnimInstance()
{
	_isMoving = false;
	_isAttacking = false;
	_isDead = false;
	_isStartPlay = false;
}

void UHSCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (_isDead)
		return;

	_character = Cast<AHSCharacterBase>(TryGetPawnOwner());

	if (IsValid(_character))
	{
		_isMoving = _character->GetMovingState();
		_isAttacking = _character->GetAttackingState();
		_isDead = _character->GetDeadState();
	}
}

void UHSCharacterAnimInstance::AnimNotify_StartPlay()
{
	_isStartPlay = true;

	_character = Cast<AHSCharacterBase>(TryGetPawnOwner());

	if (IsValid(_character))
		_character->SetPlayStart(true);
}

void UHSCharacterAnimInstance::AnimNotify_Fire()
{
	if (IsValid(_character))
	{
		if (!_isAttacking)
			return;

		FName muzzleSocket(TEXT("Muzzle_01"));
		auto bullet = GetWorld()->SpawnActor<AHSBulletBase>(_character->GetMesh()->GetSocketLocation(muzzleSocket), _character->GetBulletRotation());
		if(bullet)
			bullet->SetBulletOwner(_character);
	}
}

void UHSCharacterAnimInstance::AnimNotify_LeftPlant()
{

}

void UHSCharacterAnimInstance::AnimNotify_RightPlant()
{

}

void UHSCharacterAnimInstance::AnimNotify_AttackEnd()
{
	_character = Cast<AHSCharacterBase>(TryGetPawnOwner());

	if (IsValid(_character))
		_character->OnAttackEnd.Broadcast();
}

void UHSCharacterAnimInstance::AnimNotify_DeadEnd()
{
	GetWorld()->DestroyActor(_character);
}
