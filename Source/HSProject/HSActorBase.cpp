#include "HSActorBase.h"
#include <Particles/ParticleSystemComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/WidgetComponent.h>
#include "HSHUD.h"
#include "HSStatComponent.h"

AHSActorBase::AHSActorBase()
{
	SetCanBeDamaged(true);

	_trigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TOWERTRIGER"));
	_towerEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TOWEREFFECT"));
	_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TOWERSTATICMESH"));

	RootComponent = _trigger;
	_trigger->SetCapsuleSize(100.f, 50.f, true);
	_trigger->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	_trigger->SetCollisionProfileName(TEXT("Character"));


	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/EnvironmentPack2/Meshes/SM_ArenaBG_Spire_01.SM_ArenaBG_Spire_01'"));

	if (SM.Succeeded())
	{
		_staticMesh->SetStaticMesh(SM.Object);
	}

	_staticMesh->SetRelativeScale3D(FVector(0.15f, 0.15f, 0.15f));
	_staticMesh->SetCollisionProfileName(TEXT("Character"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_TowerEffect(TEXT("ParticleSystem'/Game/ParagonZinx/FX/Particles/Zinx/Effects/P_Zinx_EmoteGreeting_Tendril.P_Zinx_EmoteGreeting_Tendril'"));

	if (PS_TowerEffect.Succeeded())
	{
		_towerEffect->SetTemplate(PS_TowerEffect.Object);
	}

	_towerEffect->SetupAttachment(RootComponent);
	_towerEffect->bAutoActivate = true;
	_towerEffect->SetRelativeScale3D(FVector(10.f, 10.f, 10.f));
	_towerEffect->SetRelativeLocation(FVector(0.f, 0.f, 500.f));

	SetActorLocation(FVector(0.f, 0.f, 0.f));

	_statComponent = CreateDefaultSubobject<UHSStatComponent>(TEXT("STAT"));

	if (_statComponent)
	{
		_statComponent->SetActorType(2); // Tower
		_actorType = 2;
	}

	static ConstructorHelpers::FClassFinder<UHSHUD> UI_HUD(TEXT("WidgetBlueprint'/Game/UI/WBP_HSHUD.WBP_HSHUD_C'"));
	if (UI_HUD.Succeeded())
	{
		_widgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("MAINUI"));

		if (_widgetComponent)
			_widgetComponent->SetWidgetClass(UI_HUD.Class);

	}

 	PrimaryActorTick.bCanEverTick = false;
}

void AHSActorBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_widgetComponent->InitWidget();
	auto HpWidget = Cast<UHSHUD>(_widgetComponent->GetUserWidgetObject());

	if (HpWidget)
		HpWidget->BindHp(_statComponent);
}

