#include "HSProjectGameModeBase.h"
#include "HSPlayerControllerBase.h"
#include "HSCharacterBase.h"
#include <Sound/SoundWave.h>
#include <Components/AudioComponent.h>
#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include "HSGameInstance.h"
#include "HSHUD.h"
#include "HSPlayer.h"

AHSProjectGameModeBase::AHSProjectGameModeBase()
{
	PlayerControllerClass = AHSPlayerControllerBase::StaticClass();
	
	static ConstructorHelpers::FClassFinder<ACharacter> BP_Player(TEXT("Blueprint'/Game/BluePrints/BP_Player.BP_Player_C'"));
	if (BP_Player.Succeeded())
	{
		DefaultPawnClass = BP_Player.Class;
	}

	static ConstructorHelpers::FClassFinder<UHSHUD> UI_HUD(TEXT("WidgetBlueprint'/Game/UI/WBP_MainGame.WBP_MainGame_C'"));
	if (UI_HUD.Succeeded())
	{
		_HUD_Class = UI_HUD.Class;

		_mainGameWidget = CreateWidget(GetWorld(), _HUD_Class);

		if (_mainGameWidget)
		{
			_mainGameWidget->AddToViewport();
			//_mainGameWidget->RemoveFromViewport();
		}
	}
}

void AHSProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SetMainGameCharacter();
	InitializeObjectCreate();
}

UUserWidget* AHSProjectGameModeBase::GetMainGameWidget()
{
	return _mainGameWidget;
}

void AHSProjectGameModeBase::SpawnMonster()
{
	auto gameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	gameInstance->CreateLeftMonster();
	gameInstance->CreateRightMonster();
}

void AHSProjectGameModeBase::InitializeObjectCreate()
{
	auto gameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	gameInstance->CreateTower();
	GetWorldTimerManager().SetTimer(_monsterSpawnTimerHandle, this, &AHSProjectGameModeBase::SpawnMonster, 7.0f, true, 7.0f);
}

void AHSProjectGameModeBase::SetMainGameCharacter()
{
	_mainGameCharacter = Cast<AHSPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

