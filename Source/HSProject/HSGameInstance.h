// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HSGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HSPROJECT_API UHSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UHSGameInstance();

	virtual void Init() override;
	
};
