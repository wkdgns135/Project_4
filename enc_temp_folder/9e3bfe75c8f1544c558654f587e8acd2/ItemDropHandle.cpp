// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemDropHandle.h"


AItemDropHandle::AItemDropHandle()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AItemDropHandle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemDropHandle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemDropHandle::SpawnWeapon(int32 WeaponTier, int32 DropTier, FVector EnemyLocation)
{
	//if (DropOrFalse(DropTier))
	{
		EWeaponTier DropItemTier = GetItemTier(WeaponTier);
		EWeaponType DropItemType = GetItemType();

		UE_LOG(LogTemp, Warning, TEXT("Drop Item Info = Tier : %d, Type : %d"), DropItemTier, DropItemType);

		FActorSpawnParameters SpawnInfo;
		FVector DropLocation = FVector(EnemyLocation.X, EnemyLocation.Y, 0);
		ADropItemActor* DropItem = GetWorld()->SpawnActor<ADropItemActor>(ADropItemActor::StaticClass(), DropLocation, FRotator(0,0,0), SpawnInfo);
		DropItem->InitializeDropWeapon(DropItemTier, DropItemType);
	}
}

bool AItemDropHandle::DropOrFalse(int32 DropTier)
{
	bool bIsDrop = false;
	int32 DropValue = 0;

	if (DropTier >= 0 && DropTier < 3) DropValue = GetTierValue(DropTier - 1);
	if (DropValue > 50) bIsDrop = true;

	return bIsDrop;
}

EWeaponTier AItemDropHandle::GetItemTier(int32 maxTier)
{
	int32 TierValue = GetTierValue(maxTier);
	
	if (TierValue <= 20) return EWeaponTier::Normal; // 60
	else if (TierValue <= 40) return EWeaponTier::Rare; // 80
	else if (TierValue <= 60) return EWeaponTier::Epic; // 95
	else if (TierValue <= 80) return EWeaponTier::Unique; // 99
	else if (TierValue <= 100) return EWeaponTier::Legend; // 100

	return EWeaponTier::None;
}

EWeaponType AItemDropHandle::GetItemType()
{
	//¹Ì±¸Çö
	return EWeaponType::AR;
}

int32 AItemDropHandle::GetTierValue(int32 maxTier)
{
	int32 MaxRange = 100;
	int32 ResultValue = 0;

	switch (maxTier)
	{
	case 0:
		MaxRange = 60;
		break;

	case 1:
		MaxRange = 80;
		break;

	case 2:
		MaxRange = 95;
		break;

	case 3:
		MaxRange = 99;
		break;

	case 4:
		MaxRange = 100;
		break;
	}

	ResultValue = FMath::RandRange(0, MaxRange);
	
	return ResultValue;
}
