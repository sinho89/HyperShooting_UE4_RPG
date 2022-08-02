// Fill out your copyright notice in the Description page of Project Settings.


#include "HSTowerBulletBase.h"
#include <Particles/ParticleSystemComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include "DrawDebugHelpers.h"
#include <Components/BoxComponent.h>
#include "HSHitEffectBase.h"
#include "HSActorBase.h"
#include "HSStatComponent.h"

// Sets default values
AHSTowerBulletBase::AHSTowerBulletBase()
{
	_bulletEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BULLETEFFECT"));
	_trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BULLETTRIGER"));
	_moveComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BULLETMOVE"));

	RootComponent = _trigger;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_BulletEffect(TEXT("ParticleSystem'/Game/ParagonZinx/FX/Particles/Zinx/Abilities/Primary/FX/P_Zinx_Primary_Projectile.P_Zinx_Primary_Projectile'"));

	if (PS_BulletEffect.Succeeded())
	{
		_bulletEffect->SetTemplate(PS_BulletEffect.Object);
	}

	_bulletEffect->SetupAttachment(RootComponent);
	_bulletEffect->bAutoActivate = true;
	_bulletEffect->SetCollisionProfileName(TEXT("BulletCollectible"));

	_trigger->SetCollisionProfileName(TEXT("BulletCollectible"));
	_trigger->SetBoxExtent(FVector(30.f, 30.f, 30.f));

	_moveComponent->InitialSpeed = 3000.f;
	_moveComponent->ProjectileGravityScale = 0.f;
	_moveComponent->bInitialVelocityInLocalSpace = true;


	PrimaryActorTick.bCanEverTick = false;

}

void AHSTowerBulletBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (IsValid(_trigger))
		_trigger->OnComponentBeginOverlap.AddDynamic(this, &AHSTowerBulletBase::OnCharacterOverlap);
}

void AHSTowerBulletBase::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->ActorHasTag(TEXT("Tower")))
			return;

		if (OtherActor->CanBeDamaged())
		{
			if (OtherActor->ActorHasTag(TEXT("Enemy")))
			{
				FPointDamageEvent damageEvent;
				if (_bulletOwner)
					OtherActor->TakeDamage(_bulletOwner->GetStatComponent()->GetAttack(), damageEvent, NULL, _bulletOwner);
			}
		}

		GetWorld()->SpawnActor<AHSHitEffectBase>(GetActorLocation(), GetActorRotation());
		GetWorld()->DestroyActor(this);

	}
}

