#include "HSCharacterBase.h"
#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/WidgetComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/Character.h>
#include "HSCharacterAnimInstance.h"
#include "HSAIController.h"
#include "HSStatComponent.h"
#include "HSWorldWidget.h"

AHSCharacterBase::AHSCharacterBase()
{
	
	//PrimaryActorTick.bStartWithTickEnabled = true;
}

void AHSCharacterBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	_bulletRotation = FRotator::ZeroRotator;
}

void AHSCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SetAnimComponent();
	SetStatComponent();
}

void AHSCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

float AHSCharacterBase::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float damage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (_statComponent)
	{
		_statComponent->OnAttacked(damage);
	}

	return damage;
}

void AHSCharacterBase::SetAnimComponent()
{
	_animInstance = Cast<UHSCharacterAnimInstance>(GetMesh()->GetAnimInstance());
}

void AHSCharacterBase::SetStatComponent()
{
	if (_statComponent)
	{
		_statComponent->OnDead.AddLambda([this]()
			{
				_isDead = true;
				_isMoving = false;
				_isAttacking = false;
			});
	}
}

