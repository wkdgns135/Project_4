// Fill out your copyright notice in the Description page of Project Settings.
#include "System/GameManager.h"
#include "Kismet/GameplayStatics.h"
#include <Blueprint/WidgetBlueprintLibrary.h>

void UGameManager::InitWeaponData(const EWeaponTier& WeaponTier, const EWeaponType& WeaponType)
{
	this->CurrentWeaponTier = WeaponTier;
	this->CurrentWeaponType = WeaponType;
}

void UGameManager::LoadMainScene(const EWeaponTier& WeaponTier, const EWeaponType& WeaponType, const uint32 Level)
{
	InitWeaponData(WeaponTier, WeaponType);

	const UWorld* World = GetWorld();
	check(World);
	UGameplayStatics::OpenLevel(World, "PlayerShootingTestLevel");

	// 컨트롤러 가져오기
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
	if (PlayerController)
	{
		// 입력 모드 설정
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;
	}
}

FString UGameManager::GetCurrentWeaponTierName()
{
	static const UEnum* WeaponTierEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EWeaponTier"), true);
	FString WeaponTierName = WeaponTierEnum ? WeaponTierEnum->GetNameStringByValue((int64)CurrentWeaponTier) : TEXT("Defalut");
	return WeaponTierName;
}

FString UGameManager::GetCurrentWeaponTypeName()
{
	static const UEnum* WeaponTypeEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EWeaponType"), true);
	FString WeaponTypeName = WeaponTypeEnum ? WeaponTypeEnum->GetNameStringByValue((int64)CurrentWeaponType) : TEXT("Defalut");
	return WeaponTypeName;
}
