// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "../PlayerData.h"
#include "InventorySlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_4_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	EWeaponTier Tier;
	EWeaponType Type;

protected:
	virtual void NativeOnInitialized();

public:
	void InitSlot(const EWeaponType& type, const EWeaponTier& tier);
	UFUNCTION(BlueprintCallable)
	void ButtonClicked();

	UPROPERTY(meta = (BindWidget))
	UButton* Button;
	UPROPERTY(meta = (BindWidget))
	UImage* Background;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemNameText;

};
