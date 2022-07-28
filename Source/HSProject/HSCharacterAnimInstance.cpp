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

	_character = Cast<AHSCharacterBase>(TryGetPawnOwner());

	if (IsValid(_character))
	{
		_isMoving = _character->GetMovingState();
		_isAttacking = _character->GetAttackingState();
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
		GetWorld()->SpawnActor<AHSBulletBase>(_character->GetMesh()->GetSocketLocation(muzzleSocket), _character->GetBulletRotation());
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
