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
class PROJECT_4_API USaveDataManager : public UGameInstance
{
	GENERATED_BODY()
	
public:
	TArray<FWeaponSaveData> GetWeaponSaveData();
	UPlayerData* CreateSaveData();
};
