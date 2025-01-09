// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "System/PlayerData.h"
#include "Components/SphereComponent.h"
#include "PlayerCharacter.h"
#include "DropItemActor.generated.h"

UCLASS()
class PROJECT_4_API ADropItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADropItemActor();

	void InitializeDropWeapon(EWeaponTier wTier, EWeaponType wType);

	UFUNCTION()
	void PlayerOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

	EWeaponTier WeaponTier;
	EWeaponType WeaponType;
	TObjectPtr<class APlayerCharacter> Player;

	TObjectPtr<class UStaticMeshComponent> Sphere;
	TObjectPtr<class USphereComponent> SphereComponent;
	//TObjectPtr<class UMaterial> Material;
	
	FVector TierColor;
	TMap<EWeaponTier, const TCHAR*> MapTierColor;

	void SetColor();

public:	
	virtual void Tick(float DeltaTime) override;

};
