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

    // Tier�� ���� ������ �ؽ�Ʈ ���� ����
    switch (Tier)
    {
    case EWeaponTier::Default:
        BackgroundColor = FLinearColor::White; // ���: ���
        TextColor = FLinearColor::Black;       // �ؽ�Ʈ: ������
        break;
    case EWeaponTier::Normal:
        BackgroundColor = FLinearColor(0.8f, 0.8f, 0.8f, 1.0f); // ���: ���� ȸ��
        TextColor = FLinearColor::Black;                         // �ؽ�Ʈ: ������
        break;
    case EWeaponTier::Rare:
        BackgroundColor = FLinearColor(0.0f, 0.5f, 1.0f, 1.0f); // ���: �Ķ���
        TextColor = FLinearColor::White;                        // �ؽ�Ʈ: ���
        break;
    case EWeaponTier::Epic:
        BackgroundColor = FLinearColor(0.5f, 0.0f, 0.5f, 1.0f); // ���: �����
        TextColor = FLinearColor::White;                        // �ؽ�Ʈ: ���
        break;
    case EWeaponTier::Unique:
        BackgroundColor = FLinearColor(1.0f, 0.65f, 0.0f, 1.0f); // ���: ��Ȳ��
        TextColor = FLinearColor::Black;                         // �ؽ�Ʈ: ������
        break;
    case EWeaponTier::Legend:
        BackgroundColor = FLinearColor(0.0f, 1.0f, 0.0f, 1.0f); // ���: �ʷϻ� (���� ���)
        TextColor = FLinearColor::Black;                         // �ؽ�Ʈ: ������
        break;
    }

    // UImage ���� ����
    Background->SetColorAndOpacity(BackgroundColor);

    // UTextBlock ���� ����
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

