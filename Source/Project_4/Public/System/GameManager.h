// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerData.h"
#include "GameManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_4_API UGameManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
private:
	EWeaponTier CurrentWeaponTier;
	EWeaponType CurrentWeaponType;

	void InitWeaponData(const EWeaponTier& WeaponTier, const EWeaponType& WeaponType);

public:	
	void LoadMainStageScene(const EWeaponTier &WeaponTier, const EWeaponType & WeaponType, const uint32 Level);
	void LoadMainMenuScene();

	EWeaponTier GetCurrentWeaponTier() { return CurrentWeaponTier; }
	EWeaponType GetCurrentWeaponType() { return CurrentWeaponType; }
	FString GetCurrentWeaponTierName();
	FString GetCurrentWeaponTypeName();
	void SetCurrentWeaponTier(const EWeaponTier& WeaponTier);
	void SetCurrentWeaponType(const EWeaponType& WeaponType);
};
