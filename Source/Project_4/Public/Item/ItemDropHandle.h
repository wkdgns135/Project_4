// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "System/PlayerData.h"
#include "DropItemActor.h"
#include "ItemDropHandle.generated.h"

UCLASS()
class PROJECT_4_API AItemDropHandle : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemDropHandle();

	bool DropOrFalse(int32 DropTier);
	EWeaponTier GetItemTier(int32 maxTier);
	EWeaponType GetItemType();
	int32 GetTierValue(int32 maxTier);
	void SpawnWeapon(int32 WeaponTier, int32 DropTier, FVector EnemyLocation);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
