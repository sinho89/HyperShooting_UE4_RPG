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
	SetCanBeDamaged(true);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -96.f), FRotator(0.f, 0.f, 180.f));

	_statComponent = CreateDefaultSubobject<UHSStatComponent>(TEXT("STAT"));
	_bulletRotation = FRotator::ZeroRotator;

	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AHSCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AHSCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SetAnimComponent();
	SetStatComponent();
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

