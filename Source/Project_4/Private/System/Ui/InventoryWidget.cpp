// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Ui/InventoryWidget.h"
#include "System/Ui/InventorySlotWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UInventoryWidget::HideInventory()
{
    RemoveFromViewport();
}

void UInventoryWidget::UpdateInventory(const TArray<FWeaponSaveData>& WeaponSaveData)
{
    if (!InventoryGrid) return;

    InventoryGrid->ClearChildren(); // 기존 슬롯 초기화
    for (int32 i = 0; i < 25; i++)
    {
        if (i >= WeaponSaveData.Num())AddItemToGrid(EWeaponType::None, EWeaponTier::None, i);
        else AddItemToGrid(WeaponSaveData[i].WeaponType, WeaponSaveData[i].WeaponTier, i);
    }
}


void UInventoryWidget::AddItemToGrid(const EWeaponType &type, const EWeaponTier &tier, int32 Index)
{
    if (!InventorySlot) return;
    UInventorySlotWidget* NewSlot = CreateWidget<UInventorySlotWidget>(GetWorld(), InventorySlot->StaticClass());
    if (!NewSlot) return;

	NewSlot->Type = type;
	NewSlot->Tier = tier;

    static const UEnum* WeaponTypeEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EWeaponType"), true);
    static const UEnum* WeaponTierEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EWeaponTier"), true);

    // WeaponType과 WeaponTier의 이름 가져오기
    FString WeaponTypeName = WeaponTypeEnum ? WeaponTypeEnum->GetNameStringByValue((int64)type) : TEXT("Unknown");
    FString WeaponTierName = WeaponTierEnum ? WeaponTierEnum->GetNameStringByValue((int64)tier) : TEXT("Unknown");
    FString ItemName = FString::Printf(TEXT("%s(%s)"), *WeaponTypeName, *WeaponTierName);

    // 슬롯에 텍스트 추가
    UTextBlock* TextBlock = Cast<UTextBlock>(NewSlot->GetWidgetFromName(TEXT("ItemNameText")));
    if (TextBlock)
    {
        TextBlock->SetText(FText::FromString(ItemName));
    }

    InventoryGrid->AddChildToUniformGrid(NewSlot, Index / 5, Index % 5); // 5열 기준 배치
}