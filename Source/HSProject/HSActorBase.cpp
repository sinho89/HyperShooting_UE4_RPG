#include "HSActorBase.h"
#include <Particles/ParticleSystemComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/WidgetComponent.h>
#include "HSHUD.h"
#include "HSStatComponent.h"
#include "HSGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include "HSTowerHpWidget.h"

AHSActorBase::AHSActorBase()
{
	Tags.Add(TEXT("Tower"));

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

	_towerHpWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
	_towerHpWidgetComponent->SetWidgetSpace(EWidgetSpace::World);

	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("WidgetBlueprint'/Game/UI/WBP_TowerHpBar.WBP_TowerHpBar_C'"));

	if (UW.Succeeded())
	{
		_towerHpWidgetComponent->SetWidgetClass(UW.Class);
		_towerHpWidgetComponent->SetDrawSize(FVector2D(600.f, 100.f));
		
	}

 	PrimaryActorTick.bCanEverTick = false;
}

void AHSActorBase::BeginPlay()
{
	Super::BeginPlay();

	/*auto gameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	auto mainWidget = Cast<UHSHUD>(gameInstance->GetMainWidget());

	if (mainWidget)
		mainWidget->BindHp(_statComponent);*/
}

void AHSActorBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_towerHpWidgetComponent->InitWidget();

	auto HpWidget = Cast<UHSTowerHpWidget>(_towerHpWidgetComponent->GetUserWidgetObject());

	if (HpWidget)
	{
		HpWidget->AddToViewport(1);
		HpWidget->BindHp(_statComponent);
	}
}

float AHSActorBase::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (_statComponent)
	{
		_statComponent->OnAttacked(damage);
	}

	return damage;
}

