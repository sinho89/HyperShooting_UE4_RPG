// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HSTowerHpWidget.generated.h"

/**
 * 
 */
UCLASS()
class HSPROJECT_API UHSTowerHpWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindHp(class UHSStatComponent* StatComp);
	void UpdateHp();

private:
	TWeakObjectPtr<class UHSStatComponent> _currentStatComp;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* PB_TowerHpBar;
	
};
