// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Ui/AmmoWidget.h"

void UAmmoWidget::SetAmmoText(const uint32& CurrentAmmoCount, const uint32& AmmoCount)
{
	if (AmmoText) {
		FString AmmoString = FString::Printf(TEXT("%d / %d"), CurrentAmmoCount, AmmoCount);
		AmmoText->SetText(FText::FromString(AmmoString));

	}

}
