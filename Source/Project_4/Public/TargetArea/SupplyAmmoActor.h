// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "TargetArea/SupplySpawner.h"
#include "SupplyAmmoActor.generated.h"

UCLASS()
class PROJECT_4_API ASupplyAmmoActor : public AActor
{
	GENERATED_BODY()

public:	
	ASupplyAmmoActor();

	void InitializeAmmo(ASupplySpawner* Spawner);

	UFUNCTION()
	void PlayerOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	TObjectPtr<class UStaticMeshComponent> SphereMesh;
	TObjectPtr<class USphereComponent> SphereComponent;
	APlayerCharacter* Player;
};
