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
	FWeaponSaveData(): WeaponType(EWeaponType::None), WeaponTier(EWeaponTier::None) {}
	FWeaponSaveData(EWeaponType Type, EWeaponTier Tier): WeaponType(Type), WeaponTier(Tier) {}
	UPROPERTY()
	EWeaponType WeaponType;
	UPROPERTY()
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
