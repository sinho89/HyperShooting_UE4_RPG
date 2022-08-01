// Fill out your copyright notice in the Description page of Project Settings.


#include "HSEnemy.h"
#include <Components/CapsuleComponent.h>
#include <Components/WidgetComponent.h>
#include "HSCharacterAnimInstance.h"
#include "HSAIController.h"
#include "HSStatComponent.h"
#include "HSWorldWidget.h"
#include "HSPlayer.h"

AHSEnemy::AHSEnemy()
{
	Tags.Add("Enemy");

	GetCapsuleComponent()->InitCapsuleSize(45.f, 96.0f);
	
	_worldHpWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
	_worldHpWidgetComponent->SetupAttachment(GetMesh());
	_worldHpWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	_worldHpWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("WidgetBlueprint'/Game/UI/WBP_WorldHpBar.WBP_WorldHpBar_C'"));

	if (UW.Succeeded())
	{
		_worldHpWidgetComponent->SetWidgetClass(UW.Class);
		_worldHpWidgetComponent->SetDrawSize(FVector2D(300.f, 50.f));
	}

	AIControllerClass = AHSAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AHSEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AHSEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_worldHpWidgetComponent->InitWidget();

	auto HpWidget = Cast<UHSWorldWidget>(_worldHpWidgetComponent->GetUserWidgetObject());

	if (HpWidget)
		HpWidget->BindHp(_statComponent);
}

float AHSEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	
	if (_statComponent->GetHp() <= 0)
		Cast<AHSPlayer>(DamageCauser)->GetStatComponent()->OnGetExp(_statComponent->GetExpPoint());

	return damage;
}

void AHSEnemy::SetAnimComponent()
{
	Super::SetAnimComponent();
}

void AHSEnemy::SetStatComponent()
{
	Super::SetStatComponent();
}