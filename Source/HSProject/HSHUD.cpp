// Fill out your copyright notice in the Description page of Project Settings.


#include "HSHUD.h"
#include "HSStatComponent.h"
#include <Components/ProgressBar.h>

void UHSHUD::BindHp(class UHSStatComponent* StatComp)
{
	_currentStatComp = StatComp;
	_currentStatComp->OnHpChanged.AddUObject(this, &UHSHUD::UpdateHp);
}

void UHSHUD::UpdateHp()
{
	if (_currentStatComp.IsValid())
		PB_HpBar->SetPercent(_currentStatComp->GetHpRatio());
}

void UHSHUD::BindExp(class UHSStatComponent* StatComp)
{
	_currentStatComp = StatComp;
	_currentStatComp->OnExpChanged.AddUObject(this, &UHSHUD::UpdateExp);

}

void UHSHUD::UpdateExp()
{
	if (_currentStatComp.IsValid())
		PB_ExpBar->SetPercent(_currentStatComp->GetExpRatio());
}
