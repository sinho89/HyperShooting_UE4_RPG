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

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	_springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	_springArmComponent->SetupAttachment(RootComponent);
	_springArmComponent->SetUsingAbsoluteRotation(true);
	_springArmComponent->TargetArmLength = 1200.f;
	_springArmComponent->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	_springArmComponent->bDoCollisionTest = false; 

	_cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	_cameraComponent->SetupAttachment(_springArmComponent, USpringArmComponent::SocketName);
	_cameraComponent->bUsePawnControlRotation = false; 

	/*static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/ParagonZinx/Characters/Heroes/Zinx/Meshes/Zinx.Zinx'"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}*/

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -96.f), FRotator(0.f, 0.f, 180.f));

	_statComponent = CreateDefaultSubobject<UHSStatComponent>(TEXT("STAT"));

	if (_statComponent)
	{
		if (GetClass()->GetName() == TEXT("BP_Player_C"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Player Init Type"))
			_statComponent->SetActorType(0); // Player
			
			_actorType = 0;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Monster Init Type"))
			_statComponent->SetActorType(1); // Monster
			_actorType = 1;
		}
	}

	if (_actorType == 1)
	{
		_widgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
		_widgetComponent->SetupAttachment(GetMesh());
		_widgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
		_widgetComponent->SetWidgetSpace(EWidgetSpace::Screen);

		static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("WidgetBlueprint'/Game/UI/WBP_WorldHpBar.WBP_WorldHpBar_C'"));

		if (UW.Succeeded())
		{
			_widgetComponent->SetWidgetClass(UW.Class);
			_widgetComponent->SetDrawSize(FVector2D(300.f, 50.f));
		}
	}

	_bulletRotation = FRotator::ZeroRotator;

	AIControllerClass = AHSAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

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

	_widgetComponent->InitWidget();

	auto HpWidget = Cast<UHSWorldWidget>(_widgetComponent->GetUserWidgetObject());

	if (HpWidget)
		HpWidget->BindHp(_statComponent);
}

float AHSCharacterBase::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (_statComponent)
		_statComponent->OnAttacked(ActualDamage);

	return ActualDamage;
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

