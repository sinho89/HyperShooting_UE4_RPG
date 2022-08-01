// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HSHUD.generated.h"

/**
 * 
 */
UCLASS()
class HSPROJECT_API UHSHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindHp(class UHSStatComponent* StatComp);
	void UpdateHp();

	void BindExp(class UHSStatComponent* StatComp);
	void UpdateExp();

private:
	TWeakObjectPtr<class UHSStatComponent> _currentStatComp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_HpBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_ExpBar;
};
