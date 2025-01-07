// Fill out your copyright notice in the Description page of Project Settings.


#include "System/MainMenuGameMode.h"
#include "Blueprint/UserWidget.h"
#include <System/SaveDataManager.h>
#include <Kismet/GameplayStatics.h>

void AMainMenuGameMode::BeginPlay()
{
    Super::BeginPlay();
    AddLegendWeapon();
}

void AMainMenuGameMode::ShowInventory()
{
    if (InventoryWidget)
    {
        TArray<FWeaponSaveData> PlayerData = GetGameInstance()->GetSubsystem<USaveDataManager>()->GetWeaponSaveData();
        InventoryWidget->AddToViewport();
        InventoryWidget->UpdateInventory(PlayerData);
    }
}

void AMainMenuGameMode::AddLegendWeapon()
{
    UE_LOG(LogTemp, Display, TEXT("Activate cheat"));
    GetGameInstance()->GetSubsystem<USaveDataManager>()->AddWeapon(FWeaponSaveData(EWeaponType::AR, EWeaponTier::Legend));
}
