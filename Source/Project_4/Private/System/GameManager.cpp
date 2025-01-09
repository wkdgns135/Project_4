// Fill out your copyright notice in the Description page of Project Settings.
#include "System/GameManager.h"
#include "Kismet/GameplayStatics.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include <System/SaveDataManager.h>

void UGameManager::InitWeaponData(const EWeaponTier& WeaponTier, const EWeaponType& WeaponType)
{
	this->CurrentWeaponTier = WeaponTier;
	this->CurrentWeaponType = WeaponType;
}

void UGameManager::LoadMainStageScene(const EWeaponTier& WeaponTier, const EWeaponType& WeaponType, const uint32 Level)
{
	InitWeaponData(WeaponTier, WeaponType);

	const UWorld* World = GetWorld();
	check(World);
	UGameplayStatics::OpenLevel(World, "MainStageLevel");

	// 컨트롤러 가져오기
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
	if (PlayerController)
	{
		// 입력 모드 설정
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;
	}
}

void UGameManager::LoadMainMenuScene()
{
	//TODO: 여기에 코드 작성 (설명)

	if (CurrentWeaponTier != EWeaponTier::Default) {
		GetGameInstance()->GetSubsystem<USaveDataManager>()->AddWeapon({CurrentWeaponType, CurrentWeaponTier});
	}

	const UWorld* World = GetWorld();
	check(World);
	UGameplayStatics::OpenLevel(World, "MainMenuLevel");

	// 컨트롤러 가져오기
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
	if (PlayerController)
	{
		// 입력 모드 설정
		PlayerController->SetInputMode(FInputModeUIOnly());
		PlayerController->bShowMouseCursor = true;
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

void UGameManager::SetCurrentWeaponTier(const EWeaponTier& WeaponTier)
{
	CurrentWeaponTier = WeaponTier;
}

void UGameManager::SetCurrentWeaponType(const EWeaponType& WeaponType)
{
	CurrentWeaponType = WeaponType;
}
