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
	_character = NULL;
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
	TArray<FHitResult> overlapResults;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(_character);

	float attackRange = 150.f;
	float attackRadius = 50.f;

	bool bResult = GetWorld()->SweepMultiByChannel(
		OUT overlapResults,
		_character->GetActorLocation(),
		_character->GetActorLocation() + _character->GetActorForwardVector() * attackRange + _character->GetActorUpVector() * 1.0f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(attackRadius),
		QueryParams);

	if (bResult)
	{
		for (auto& overlapResult : overlapResults)
		{
			if (overlapResult.GetActor()->ActorHasTag(TEXT("Player")))
			{
				if (_character->ActorHasTag(TEXT("Enemy")))
				{
					FPointDamageEvent damageEvent;
					auto enemy = Cast<AHSEnemy>(_character);
					overlapResult.GetActor()->TakeDamage(
						enemy->GetStatComponent()->GetAttack(),
						damageEvent, enemy->GetController(), enemy);

					UE_LOG(LogTemp, Error, TEXT("Collision Player"));
					break;
				}
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
