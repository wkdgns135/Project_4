// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Ui/InventorySlotWidget.h"
#include "System/GameManager.h"
#include "Kismet/GameplayStatics.h"

void UInventorySlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Button->OnClicked.AddDynamic(this, &UInventorySlotWidget::ButtonClicked);
}

void UInventorySlotWidget::InitSlot(const EWeaponType& type, const EWeaponTier& tier)
{
	Type = type;
	Tier = tier;
}

void UInventorySlotWidget::ButtonClicked()
{
	GetGameInstance()->GetSubsystem<UGameManager>()->LoadMainScene(Tier, Type, 1);
}

