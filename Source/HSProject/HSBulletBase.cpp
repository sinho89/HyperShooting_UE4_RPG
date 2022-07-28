// Fill out your copyright notice in the Description page of Project Settings.


#include "HSBulletBase.h"
#include <Particles/ParticleSystemComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include "DrawDebugHelpers.h"
#include <Components/BoxComponent.h>
#include "HSHitEffectBase.h"

// Sets default values
AHSBulletBase::AHSBulletBase()
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

	InitialLifeSpan = 1.0f;
	

	PrimaryActorTick.bCanEverTick = false;

}

void AHSBulletBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if(IsValid(_trigger))
		_trigger->OnComponentBeginOverlap.AddDynamic(this, &AHSBulletBase::OnCharacterOverlap);
}

void AHSBulletBase::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bFromSweep && OtherActor)
	{
		GetWorld()->SpawnActor<AHSHitEffectBase>(GetActorLocation(), GetActorRotation());
		GetWorld()->DestroyActor(this);
		//GetWorld()->DestroyActor(OtherActor);
	}
}

