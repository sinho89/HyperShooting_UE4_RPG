// Fill out your copyright notice in the Description page of Project Settings.


#include "HSHUD.h"
#include <Components/ProgressBar.h>

void UHSHUD::SetGageValue(float Value, float MaxValue, int Type /*= 0*/)
{
	if (Type == 0) // HP
		HpGage->Percent = Value / MaxValue;
	else if (Type == 1) // MP
		MpGage->Percent = Value / MaxValue;
	else if (Type == 2) // EXP
		ExpGage->Percent = Value / MaxValue;
}
