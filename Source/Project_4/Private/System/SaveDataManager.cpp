// Fill out your copyright notice in the Description page of Project Settings.


#include "System/SaveDataManager.h"
#include <Kismet/GameplayStatics.h>

void USaveDataManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	MaxWeaponData = 25;
}

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
	NewPlayerData->WeaponSaveData.Add(FWeaponSaveData(EWeaponType::AR, EWeaponTier::Default));
	if (!UGameplayStatics::SaveGameToSlot(NewPlayerData, "Player", 0))
	{
		UE_LOG(LogClass, Warning, TEXT("SaveGame Error!"));
	}
	return NewPlayerData;
}

void USaveDataManager::AddWeapon(const FWeaponSaveData data)
{
	UPlayerData* NewPlayerData = NewObject<UPlayerData>();
	NewPlayerData->WeaponSaveData = GetWeaponSaveData();

	//FIX ME: �̱��� MaxWeaponData �޸� ������ �ȵǴ� ���� �ذ�
	if (NewPlayerData->WeaponSaveData.Num() >= MaxWeaponData) {
		UE_LOG(LogClass, Warning, TEXT("Weapon data out of range!"));
		return;
	}

	NewPlayerData->WeaponSaveData.Add(data);
	if (!UGameplayStatics::SaveGameToSlot(NewPlayerData, "Player", 0))
	{
		UE_LOG(LogClass, Warning, TEXT("SaveGame Error!"));
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("Weapon saved: Type=%d, Tier=%d"), static_cast<int32>(data.WeaponType), static_cast<int32>(data.WeaponTier));
	}
}
