// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "SupplySpawner.generated.h"

UCLASS()
class PROJECT_4_API ASupplySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ASupplySpawner();

	UPROPERTY(EditAnywhere, Category = "Supply")
	FVector SupplyPointHealKit;

	UPROPERTY(EditAnywhere, Category = "Supply")
	FVector SupplyPointAmmo;

	UPROPERTY(EditAnywhere, Category = "Supply")
	int SupplyTimeAmmo;

	UPROPERTY(EditAnywhere, Category = "Supply")
	int SupplyTimeHealKit;

	UPROPERTY(EditDefaultsOnly, Category = "Supply")
	TSubclassOf<class AActor> Ammo;

	UPROPERTY(EditDefaultsOnly, Category = "Supply")
	TSubclassOf<class AActor> HealKit;

	APlayerCharacter* GetPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:	
	float CurrentAmmoTime;
	float CurrentHealKitTime;
	TObjectPtr<class APlayerCharacter> Player;

	class ASupplyAmmoActor* AmmoInstance;
	class ASupplyHealKitActor* HealKitInstance;

	void SpawnAmmo();
	void SpawnHealKit();

};
