// Fill out your copyright notice in the Description page of Project Settings.


#include "HSPlayerControllerBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "HSCharacterBase.h"
#include "Engine/World.h"

AHSPlayerControllerBase::AHSPlayerControllerBase()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	_isMoveClick = false;
	_isAttackClick = false;
	_isStartPlay = false;
	_moveDistance = 120.f;
}

void AHSPlayerControllerBase::BeginPlayingState()
{
	Super::BeginPlayingState();

	_player = Cast<AHSCharacterBase>(GetPawn());

	if (IsValid(_player))
		_moveToPos = _player->GetActorLocation();

	_attackToPos = FVector::ZeroVector;
}

void AHSPlayerControllerBase::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (!_isStartPlay)
	{
		GameStartCheck();
		return;
	}

	Attacking();
	Moving();
}

void AHSPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AHSPlayerControllerBase::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AHSPlayerControllerBase::OnSetDestinationReleased);

	InputComponent->BindAction("Attack", IE_Pressed, this, &AHSPlayerControllerBase::OnAttackPressed);
	InputComponent->BindAction("Attack", IE_Released, this, &AHSPlayerControllerBase::OnAttackReleased);

}

void AHSPlayerControllerBase::Moving()
{
	if (_isMoveClick)
	{
		CancleAttack();
		MoveToMouseCursor();
	}
	else
	{
		if (IsValid(_player))
		{
			if (!_player->GetMovingState())
				return;

			float const Distance = FVector::Dist(_moveToPos, _player->GetActorLocation());
			if ((Distance < _moveDistance))
				_player->SetMovingState(false);
		}
	}
}

void AHSPlayerControllerBase::MoveToMouseCursor()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	_moveToPos = Hit.ImpactPoint;

	if (Hit.bBlockingHit)
		SetNewMoveDestination(_moveToPos);
}

void AHSPlayerControllerBase::SetNewMoveDestination(const FVector DestLocation)
{
	if (IsValid(_player))
	{
		float const Distance = FVector::Dist(DestLocation, _player->GetActorLocation());

		if ((Distance > _moveDistance))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
			_player->SetMovingState(true);
		}
	}
}

void AHSPlayerControllerBase::OnSetDestinationPressed()
{
	_isMoveClick = true;
}

void AHSPlayerControllerBase::OnSetDestinationReleased()
{
	_isMoveClick = false;
}

void AHSPlayerControllerBase::CancleMove()
{
	if (IsValid(_player))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, _player->GetActorLocation());
		_player->SetMovingState(false);
		_isMoveClick = false;
	}
}

void AHSPlayerControllerBase::Attacking()
{
	if (_isAttackClick)
	{
		CancleMove();
		AttackToMouseCursor();
	}
	else
	{
		if (IsValid(_player))
		{
			if (!_player->GetAttackingState())
				return;
			_player->SetAttackingState(false);
		}
	}
}

void AHSPlayerControllerBase::AttackToMouseCursor()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	_attackToPos = Hit.ImpactPoint;

	/*if (Hit.GetActor()->Name)
		_attackToPos = Hit.GetActor()->GetActorLocation();*/

	if (Hit.bBlockingHit)
		SetAttacking(_attackToPos);
}

void AHSPlayerControllerBase::SetAttacking(const FVector DestLocation)
{
	if (IsValid(_player))
	{
		FVector const attackDir = DestLocation - _player->GetActorLocation();
		FRotator attackRotation = FRotator(0.f, attackDir.Rotation().Yaw, 0.f);

		_player->SetBulletRotation(attackRotation);
		_player->SetActorRelativeRotation(attackRotation);
		_player->SetAttackingState(true);
	}
}

void AHSPlayerControllerBase::OnAttackPressed()
{
	_isAttackClick = true;
}

void AHSPlayerControllerBase::OnAttackReleased()
{
	_isAttackClick = false;
}

void AHSPlayerControllerBase::CancleAttack()
{
	_isAttackClick = false;
}

void AHSPlayerControllerBase::GameStartCheck()
{
	if (IsValid(_player))
		_isStartPlay = _player->GetPlayStart();
}
