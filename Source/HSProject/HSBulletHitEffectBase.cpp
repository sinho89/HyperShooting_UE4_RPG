// Fill out your copyright notice in the Description page of Project Settings.


#include "HSBulletHitEffectBase.h"
#include <Particles/ParticleSystemComponent.h>
#include "DrawDebugHelpers.h"
#include <Components/BoxComponent.h>

// Sets default values
AHSBulletHitEffectBase::AHSBulletHitEffectBase()
{
	_hitEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HITEFFECT"));
	_trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("HITTRIGER"));

	RootComponent = _trigger;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_HitEffect(TEXT("ParticleSystem'/Game/ParagonZinx/FX/Particles/Zinx/Abilities/Primary/FX/P_Zinx_Primary_HitWorld.P_Zinx_Primary_HitWorld'"));

	if (PS_HitEffect.Succeeded())
	{
		_hitEffect->SetTemplate(PS_HitEffect.Object);
	}

	_hitEffect->SetupAttachment(RootComponent);
	_hitEffect->bAutoActivate = true;
	_hitEffect->SetCollisionProfileName(TEXT("No collision"));

	_trigger->SetCollisionProfileName(TEXT("No collision"));
	
	InitialLifeSpan = 1.0f;

	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AHSBulletHitEffectBase::BeginPlay()
{
	Super::BeginPlay();
	
}


