#include "HSProjectGameModeBase.h"
#include "HSPlayerControllerBase.h"
#include "HSCharacterBase.h"
#include <Sound/SoundWave.h>
#include <Components/AudioComponent.h>
#include <Kismet/GameplayStatics.h>
#include "HSGameInstance.h"
#include "HSHUD.h"

AHSProjectGameModeBase::AHSProjectGameModeBase()
{
	PlayerControllerClass = AHSPlayerControllerBase::StaticClass();
	
	static ConstructorHelpers::FClassFinder<ACharacter> BP_Player(TEXT("Blueprint'/Game/BluePrints/BP_HSCharacterBase.BP_HSCharacterBase_C'"));
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
		{
			_currentWidget->AddToViewport();
			//_currentWidget->RemoveFromViewport();
		}
	}


}

