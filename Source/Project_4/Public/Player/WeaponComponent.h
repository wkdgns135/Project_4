// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Player/WeaponData.h"
#include "Components/SkeletalMeshComponent.h"
#include "Player/Ui/UiComponent.h"
#include "../System/GenericPool.h"
#include "WeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_4_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
    FVector GetMuzzleLocation() const;
    FVector CalculateShootDirection(const FVector& MuzzleLocation, const FVector& HitLocation) const;
    void GetScreenCenterWorldLocationAndDirection(FVector& OutWorldLocation, FVector& OutWorldDirection) const;
    void SpawnProjectile(const FVector& MuzzleLocation, const FVector& ShootDirection);
    void ApplyCameraShake() const;
    void Shoot();

    USkeletalMeshComponent* SkeletalMeshComponent;
    UUiComponent* UiComponent;
    UPROPERTY(EditAnywhere, Category = "Weapon")
    UWeaponData* WeaponData;
    FTimerHandle ShootingTimerHandle;

    int32 CurrentAmmoCount;
    int32 AmmoCount;
    int32 AmmoLimit;
    bool IsShooting;
    float LastFireTime;

    AGenericPool *ProjectilePool;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void FireWeapon();

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void StopFireWeapon();

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void ReloadWeapon();

    void IncreaseAmmo(const uint32 Ammo);
};
