// Fill out your copyright notice in the Description page of Project Settings.


#include "System/SaveDataManager.h"
#include <Kismet/GameplayStatics.h>

TArray<FWeaponSaveData> USaveDataManager::GetWeaponSaveData()
{
    UPlayerData* PlayerData = Cast<UPlayerData>(UGameplayStatics::LoadGameFromSlot("Player", 0));
    if (nullptr == PlayerData)
    {
        PlayerData = CreateSaveData(); // Gets the mutable default object of a class.
    }
    return PlayerData->WeaponSaveData;
}

UPlayerData* USaveDataManager::CreateSaveData()
{
	UPlayerData* NewPlayerData = NewObject<UPlayerData>();
	NewPlayerData->WeaponSaveData = TArray<FWeaponSaveData>();
	NewPlayerData->WeaponSaveData.Add({ EWeaponType::AR, EWeaponTier::Default });
	if (!UGameplayStatics::SaveGameToSlot(NewPlayerData, "Player", 0))
	{
		UE_LOG(LogClass, Warning, TEXT("SaveGame Error!"));
	}
	return NewPlayerData;
}
