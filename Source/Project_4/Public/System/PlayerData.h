// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayerData.generated.h"

UENUM()
enum class EWeaponType
{
	AR,
	None,
};

UENUM()
enum class EWeaponTier
{
	Default,
	Normal,
	Rare,
	Epic,
	Unique,
	Legend,
	None,
};

USTRUCT()
struct FWeaponSaveData
{
	GENERATED_BODY()
public:
	EWeaponType WeaponType;
	EWeaponTier WeaponTier;
};

UCLASS()
class PROJECT_4_API UPlayerData : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<FWeaponSaveData> WeaponSaveData;
};
