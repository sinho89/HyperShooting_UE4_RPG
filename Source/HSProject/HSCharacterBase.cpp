#include "HSCharacterBase.h"
#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/Character.h>
#include "HSCharacterAnimInstance.h"
#include "HSAIController.h"

AHSCharacterBase::AHSCharacterBase()
{
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

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/ParagonZinx/Characters/Heroes/Zinx/Meshes/Zinx.Zinx'"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -96.f), FRotator(0.f, 0.f, 180.f));

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

	_animInstance = Cast<UHSCharacterAnimInstance>(GetMesh()->GetAnimInstance());

	if (_animInstance)
	{

	}
}


