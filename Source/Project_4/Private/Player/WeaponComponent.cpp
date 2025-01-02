// Fill out your copyright notice in the Description page of Project Settings.
#include "Player/WeaponComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Player/Projectile.h"
#include <Player/Ui/UiComponent.h>
#include "Player/Ui/UiCameraShake.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (OwnerCharacter)
    {
        SkeletalMeshComponent = OwnerCharacter->GetMesh();
        UiComponent = OwnerCharacter->FindComponentByClass<UUiComponent>();
    }

    CurrentAmmoCount = WeaponData->AmmoCount;
    IsShooting = false;
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}



void UWeaponComponent::GetMuzzleLocationAndRotation(FVector& OutLocation, FRotator& OutRotation) const
{
    FTransform SocketTransform = SkeletalMeshComponent->GetSocketTransform("Muzzle", RTS_World);
    OutLocation = SocketTransform.GetLocation();
    OutRotation = SocketTransform.GetRotation().Rotator();
}

void UWeaponComponent::GetScreenCenterWorldLocationAndDirection(FVector& OutWorldLocation, FVector& OutWorldDirection) const
{
    FVector2D ViewportSize;
    GEngine->GameViewport->GetViewportSize(ViewportSize);
    FVector2D ScreenCenter(ViewportSize.X / 2, ViewportSize.Y / 2);
    UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(GetWorld(), 0), ScreenCenter, OutWorldLocation, OutWorldDirection);
}

bool UWeaponComponent::PerformLineTrace(const FVector& Start, const FVector& End, FHitResult& OutHitResult) const
{
    return GetWorld()->LineTraceSingleByChannel(OutHitResult, Start, End, ECC_Visibility);
}

FVector UWeaponComponent::CalculateShootDirection(const FVector& MuzzleLocation, const FVector& HitLocation) const
{
    FVector ShootDirection = (HitLocation - MuzzleLocation).GetSafeNormal();
    float AimSize = UiComponent->GetAimSize();
    float RandomConeHalfAngle = FMath::DegreesToRadians(AimSize / 100.0f);
    return FMath::VRandCone(ShootDirection, RandomConeHalfAngle);
}

void UWeaponComponent::SpawnProjectile(const FVector& MuzzleLocation, const FVector& ShootDirection)
{
    FActorSpawnParameters SpawnParams;
    AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(AProjectile::StaticClass(), MuzzleLocation, ShootDirection.Rotation(), SpawnParams);
    if (Projectile)
    {
        Projectile->ShootInDirection(ShootDirection, WeaponData->ProjectileSpeed);
    }
}

void UWeaponComponent::ApplyCameraShake() const
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController)
    {
        PlayerController->ClientStartCameraShake(UUiCameraShake::StaticClass(), WeaponData->Recoil);
    }
}

void UWeaponComponent::FireWeapon()
{
    if (CurrentAmmoCount == 0 || !SkeletalMeshComponent || !UiComponent) return;
    IsShooting = true;

    FVector MuzzleLocation;
    FRotator MuzzleRotation;
    GetMuzzleLocationAndRotation(MuzzleLocation, MuzzleRotation);

    FVector WorldLocation;
    FVector WorldDirection;
    GetScreenCenterWorldLocationAndDirection(WorldLocation, WorldDirection);

    FVector Start = WorldLocation;
    FVector End = Start + (WorldDirection * 10000);

    FHitResult HitResult;
    FVector HitLocation = End;
    if (PerformLineTrace(Start, End, HitResult))
    {
        HitLocation = HitResult.Location;
    }

    FVector ShootDirection = CalculateShootDirection(MuzzleLocation, HitLocation);
    SpawnProjectile(MuzzleLocation, ShootDirection);
    ApplyCameraShake();

    CurrentAmmoCount--;
}

void UWeaponComponent::ReloadWeapon()
{
    CurrentAmmoCount = WeaponData->AmmoCount;
}