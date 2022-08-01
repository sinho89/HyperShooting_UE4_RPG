// Fill out your copyright notice in the Description page of Project Settings.


#include "HSWorldWidget.h"
#include "HSStatComponent.h"
#include "Components/ProgressBar.h"

void UHSWorldWidget::BindHp(class UHSStatComponent* StatComp)
{
	_currentStatComp = StatComp;
	_currentStatComp->OnHpChanged.AddUObject(this, &UHSWorldWidget::UpdateHp);
}

void UHSWorldWidget::UpdateHp()
{
	if(_currentStatComp.IsValid())
		PB_HpBar->SetPercent(_currentStatComp->GetHpRatio());
}
