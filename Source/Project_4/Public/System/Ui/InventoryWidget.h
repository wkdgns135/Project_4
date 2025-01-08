// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../PlayerData.h"
#include "InventorySlotWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_4_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    void UpdateInventory(const TArray<FWeaponSaveData>& WeaponSaveData);

protected:
    UPROPERTY(meta = (BindWidget))
    class UUniformGridPanel* InventoryGrid;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TSubclassOf<class UUserWidget> InventorySlotWidget;

    UFUNCTION(BlueprintCallable, Category = "Ui")
    void HideInventory();

private:
    void AddItemToGrid(const EWeaponType& type, const EWeaponTier& tier, int32 Index);
};
