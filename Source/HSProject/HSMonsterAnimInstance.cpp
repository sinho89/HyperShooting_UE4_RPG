#include "HSMonsterAnimInstance.h"
#include "HSMonsterBase.h"
#include <Particles/ParticleSystemComponent.h>
#include <Components/BoxComponent.h>

UHSMonsterAnimInstance::UHSMonsterAnimInstance()
{
	_isMoving = false;
	_isAttacking = false;
	_isStartPlay = false;
}

void UHSMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	_monster = Cast<AHSMonsterBase>(TryGetPawnOwner());

	if (IsValid(_monster))
	{
		_isMoving = _monster->GetMovingState();
		_isAttacking = _monster->GetAttackingState();
	}
}