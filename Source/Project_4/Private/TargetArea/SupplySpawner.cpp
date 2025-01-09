// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetArea/SupplySpawner.h"
#include "TargetArea/SupplyAmmoActor.h"
#include "TargetArea/SupplyHealKitActor.h"


ASupplySpawner::ASupplySpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	CurrentAmmoTime = CurrentHealKitTime = 0;

	SupplyPointAmmo = FVector(-100, -100, 0);
	SupplyPointHealKit = FVector(100, 100, 0);

	SupplyTimeAmmo = 10;
	SupplyTimeHealKit = 10;
}

void ASupplySpawner::BeginPlay()
{
	Super::BeginPlay();

	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass());
	Player = Cast<APlayerCharacter>(actor);
}

void ASupplySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentAmmoTime += DeltaTime;
	CurrentHealKitTime += DeltaTime;

	if (CurrentAmmoTime >= SupplyTimeAmmo)
	{
		SpawnAmmo();
		CurrentAmmoTime = 0;
	}

	if (CurrentHealKitTime >= SupplyTimeHealKit)
	{
		SpawnHealKit();
		CurrentHealKitTime = 0;
	}
}

void ASupplySpawner::SpawnAmmo()
{
	if (AmmoInstance == nullptr)
	{
		AmmoInstance = Cast<ASupplyAmmoActor>(GetWorld()->SpawnActor<AActor>(Ammo, SupplyPointAmmo, FRotator(0, 0, 0)));
		AmmoInstance->InitializeAmmo(this);
	}
}

void ASupplySpawner::SpawnHealKit()
{
	if (HealKitInstance == nullptr)
	{
		HealKitInstance = Cast<ASupplyHealKitActor>(GetWorld()->SpawnActor<AActor>(HealKit, SupplyPointHealKit, FRotator(0, 0, 0)));
		HealKitInstance->InitializeHealKit(this);
	}
}

APlayerCharacter* ASupplySpawner::GetPlayer()
{
	return Player;
}