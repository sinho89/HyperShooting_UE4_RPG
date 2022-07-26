#include "HSProjectGameModeBase.h"
#include "HSPlayerControllerBase.h"
#include "HSCharacterBase.h"
#include <Sound/SoundWave.h>
#include <Components/AudioComponent.h>
#include <Kismet/GameplayStatics.h>
#include "HSGameInstance.h"

AHSProjectGameModeBase::AHSProjectGameModeBase()
{
	PlayerControllerClass = AHSPlayerControllerBase::StaticClass();
	
	static ConstructorHelpers::FClassFinder<ACharacter> BP_Player(TEXT("Blueprint'/Game/BluePrints/BP_HSCharacterBase.BP_HSCharacterBase_C'"));
	if (BP_Player.Succeeded())
	{
		DefaultPawnClass = BP_Player.Class;
	}
}

