// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../PlayerData.h"
#include "InventorySlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_4_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	EWeaponTier Tier;
	EWeaponType Type;
};
