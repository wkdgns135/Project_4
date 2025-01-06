// Fill out your copyright notice in the Description page of Project Settings.


#include "System/MainMenuGameMode.h"
#include "Blueprint/UserWidget.h"
#include <System/SaveDataManager.h>
#include <Kismet/GameplayStatics.h>

void AMainMenuGameMode::BeginPlay()
{
    Super::BeginPlay();
}

void AMainMenuGameMode::ShowInventory()
{
    if (InventoryWidget)
    {
        TArray<FWeaponSaveData> PlayerData = Cast<USaveDataManager>(GetGameInstance())->GetWeaponSaveData();
        InventoryWidget->AddToViewport();
        InventoryWidget->UpdateInventory(PlayerData);
    }

}