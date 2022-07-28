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
	void SetGageValue(float Value, float MaxValue, int Type = 0);

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HpGage;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* MpGage;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ExpGage;
};
