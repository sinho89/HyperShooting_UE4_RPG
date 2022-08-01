#include "HSPlayer.h"
#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/WidgetComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include "HSCharacterAnimInstance.h"
#include "HSStatComponent.h"
#include "HSHUD.h"
#include "HSGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include "HSProjectGameModeBase.h"

AHSPlayer::AHSPlayer()
{
	Tags.Add("Player");
	UE_LOG(LogTemp, Error, TEXT("Player Init"));
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
	_springArmComponent->SetRelativeRotation(FRotator(-50.f, 0.f, 0.f));
	_springArmComponent->bDoCollisionTest = false;

	_cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	_cameraComponent->SetupAttachment(_springArmComponent, USpringArmComponent::SocketName);
	_cameraComponent->bUsePawnControlRotation = false;

}

void AHSPlayer::BeginPlay()
{
	Super::BeginPlay();

	AHSProjectGameModeBase* gameMode= Cast<AHSProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	auto mainWidget = Cast<UHSHUD>(gameMode->GetMainGameWidget());

	if (mainWidget)
	{
		mainWidget->BindHp(_statComponent);
		mainWidget->BindExp(_statComponent);
	}
}

void AHSPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

float AHSPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	
	return damage;
}

void AHSPlayer::SetAnimComponent()
{
	Super::SetAnimComponent();
}

void AHSPlayer::SetStatComponent()
{
	Super::SetStatComponent();
}
