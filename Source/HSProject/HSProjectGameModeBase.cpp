#include "HSProjectGameModeBase.h"
#include "HSPlayerControllerBase.h"
#include "HSCharacterBase.h"
#include <Sound/SoundWave.h>
#include <Components/AudioComponent.h>
#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include "HSGameInstance.h"
#include "HSHUD.h"

AHSProjectGameModeBase::AHSProjectGameModeBase()
{
	PlayerControllerClass = AHSPlayerControllerBase::StaticClass();
	
	static ConstructorHelpers::FClassFinder<ACharacter> BP_Player(TEXT("Blueprint'/Game/BluePrints/BP_Player.BP_Player_C'"));
	if (BP_Player.Succeeded())
	{
		DefaultPawnClass = BP_Player.Class;
	}

	static ConstructorHelpers::FClassFinder<UHSHUD> UI_HUD(TEXT("WidgetBlueprint'/Game/UI/WBP_HSHUD.WBP_HSHUD_C'"));
	if (UI_HUD.Succeeded())
	{
		_HUD_Class = UI_HUD.Class;
		_currentWidget = CreateWidget(GetWorld(), _HUD_Class);
		
		if (_currentWidget)
			_currentWidget->AddToViewport();
	}
}

void AHSProjectGameModeBase::InitGameState()
{
	Super::InitGameState();

	InitializeMainUI();
	InitializeObjectCreate();
}

void AHSProjectGameModeBase::SpawnMonster()
{
	auto gameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	gameInstance->CreateLeftMonster();
	gameInstance->CreateRightMonster();
}

void AHSProjectGameModeBase::InitializeMainUI()
{

}

void AHSProjectGameModeBase::InitializeObjectCreate()
{
	auto gameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	gameInstance->CreateTower();
	GetWorldTimerManager().SetTimer(_leftMonsterSpawnTimerHandle, this, &AHSProjectGameModeBase::SpawnMonster, 7.0f, true);
}

