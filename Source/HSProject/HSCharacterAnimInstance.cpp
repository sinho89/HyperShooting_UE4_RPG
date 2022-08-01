// Fill out your copyright notice in the Description page of Project Settings.


#include "HSCharacterAnimInstance.h"
#include "HSCharacterBase.h"
#include "HSBulletBase.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include <Particles/ParticleSystemComponent.h>
#include <Components/BoxComponent.h>
#include "HSStatComponent.h"
#include "HSEnemy.h"
#include "HSPlayer.h"
#include "DrawDebugHelpers.h"

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

void UHSCharacterAnimInstance::AnimNotify_AttackHit()
{
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, _character);

	float attackRange = 10.f;
	float attackRadius = 200.f;

	bool bResult = GetWorld()->SweepSingleByChannel(
		OUT hitResult,
		_character->GetActorLocation(),
		_character->GetActorLocation() + _character->GetActorForwardVector() * attackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel18,
		FCollisionShape::MakeSphere(attackRadius),
		params);

	FVector Vec = _character->GetActorForwardVector() * attackRange;
	FVector Center = _character->GetActorLocation() + Vec * 0.5f;
	float HalfHeight = attackRange * 0.5f + attackRadius;
	FQuat Rotation = FRotationMatrix::MakeFromZ(Vec).ToQuat();
	FColor DrawColor;

	if (bResult)
		DrawColor = FColor::Green;
	else
		DrawColor = FColor::Red;

	DrawDebugCapsule(GetWorld(), Center, HalfHeight, attackRadius,
		Rotation, DrawColor, false, 2.f);

	if (bResult && hitResult.Actor.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("%s"), *hitResult.Actor->GetName());
		if (hitResult.Actor->ActorHasTag(TEXT("Player")))
		{
			FPointDamageEvent damageEvent;

			if (_character->ActorHasTag(TEXT("Enemy")))
			{
				auto enemy = Cast<AHSEnemy>(_character);
				hitResult.Actor->TakeDamage(
					enemy->GetStatComponent()->GetAttack(),
					damageEvent, enemy->GetController(), enemy);
			}
		}

	}
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
