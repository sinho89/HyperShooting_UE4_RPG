// Fill out your copyright notice in the Description page of Project Settings.


#include "HSHUD.h"
#include "HSStatComponent.h"
#include <Components/ProgressBar.h>


void UHSHUD::BindHp(class UHSStatComponent* StatComp)
{
	_currentStatComp = StatComp;
	_currentStatComp->OnHpChanged.AddUObject(this, &UHSHUD::UpdateHp);
	UE_LOG(LogTemp, Error, TEXT("Bind Tower HP"));
}

void UHSHUD::UpdateHp()
{
	if (_currentStatComp.IsValid())
	{
		TowerHpGage->SetPercent(_currentStatComp->GetHpRatio());
		UE_LOG(LogTemp, Error, TEXT("Bind Tower Update HP"));
	}
}
