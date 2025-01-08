// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Ui/InventorySlotWidget.h"
#include "System/GameManager.h"
#include "Kismet/GameplayStatics.h"

void UInventorySlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Button->OnClicked.AddDynamic(this, &UInventorySlotWidget::ButtonClicked);
}

void SetBackgroundAndTextColor(UImage* Background, UTextBlock* ItemNameText, const EWeaponTier& Tier)
{
    if (!Background || !ItemNameText)
    {
        UE_LOG(LogTemp, Warning, TEXT("Background or ItemNameText is null."));
        return;
    }

    FLinearColor BackgroundColor;
    FLinearColor TextColor;

    // Tier에 따라 배경색과 텍스트 색상 설정
    switch (Tier)
    {
    case EWeaponTier::Default:
        BackgroundColor = FLinearColor::White; // 배경: 흰색
        TextColor = FLinearColor::Black;       // 텍스트: 검은색
        break;
    case EWeaponTier::Normal:
        BackgroundColor = FLinearColor(0.8f, 0.8f, 0.8f, 1.0f); // 배경: 밝은 회색
        TextColor = FLinearColor::Black;                         // 텍스트: 검은색
        break;
    case EWeaponTier::Rare:
        BackgroundColor = FLinearColor(0.0f, 0.5f, 1.0f, 1.0f); // 배경: 파란색
        TextColor = FLinearColor::White;                        // 텍스트: 흰색
        break;
    case EWeaponTier::Epic:
        BackgroundColor = FLinearColor(0.5f, 0.0f, 0.5f, 1.0f); // 배경: 보라색
        TextColor = FLinearColor::White;                        // 텍스트: 흰색
        break;
    case EWeaponTier::Unique:
        BackgroundColor = FLinearColor(1.0f, 0.65f, 0.0f, 1.0f); // 배경: 주황색
        TextColor = FLinearColor::Black;                         // 텍스트: 검은색
        break;
    case EWeaponTier::Legend:
        BackgroundColor = FLinearColor(1.0f, 0.84f, 0.0f, 1.0f); // 배경: 금색
        TextColor = FLinearColor::Black;                         // 텍스트: 검은색
        break;
    }

    // UImage 색상 변경
    Background->SetColorAndOpacity(BackgroundColor);

    // UTextBlock 색상 변경
    ItemNameText->SetColorAndOpacity(FSlateColor(TextColor));
}


void UInventorySlotWidget::InitSlot(const EWeaponType& type, const EWeaponTier& tier)
{
	Type = type;
	Tier = tier;
    SetBackgroundAndTextColor(Background, ItemNameText, tier);
    if (tier == EWeaponTier::None) {
        Button->SetIsEnabled(false);
    }
}

void UInventorySlotWidget::ButtonClicked()
{
	GetGameInstance()->GetSubsystem<UGameManager>()->LoadMainScene(Tier, Type, 1);
}

