// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlayerData.h"
#include "SaveDataManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_4_API USaveDataManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
private:
	int32 MaxWeaponData;
public:
	TArray<FWeaponSaveData> GetWeaponSaveData();
	UPlayerData* CreateSaveData();
	void AddWeapon(const FWeaponSaveData data);
};
