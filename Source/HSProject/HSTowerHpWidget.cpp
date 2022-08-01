#include "HSTowerHpWidget.h"
#include "HSStatComponent.h"
#include "Components/ProgressBar.h"

void UHSTowerHpWidget::BindHp(UHSStatComponent* StatComp)
{
	_currentStatComp = StatComp;
	_currentStatComp->OnHpChanged.AddUObject(this, &UHSTowerHpWidget::UpdateHp);
}

void UHSTowerHpWidget::UpdateHp()
{
	if (_currentStatComp.IsValid())
		PB_TowerHpBar->SetPercent(_currentStatComp->GetHpRatio());
}
