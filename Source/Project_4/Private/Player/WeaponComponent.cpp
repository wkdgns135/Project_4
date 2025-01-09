// Fill out your copyright notice in the Description page of Project Settings.
#include "Player/WeaponComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Player/Projectile.h"
#include "Player/Ui/UiComponent.h"
#include "Player/Ui/UiCameraShake.h"
#include "System/GenericPool.h"
#include "System/GameManager.h"

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

    UGameInstance* GameInstance = GetWorld()->GetGameInstance();
    if (GameInstance)
    {
        UGameManager* GameManager = GameInstance->GetSubsystem<UGameManager>();
        if (GameManager)
        {
            FString WeaponTypeName = GameManager->GetCurrentWeaponTypeName();
            FString WeaponTierName = GameManager->GetCurrentWeaponTierName();

            FString WeaponName = FString::Printf(TEXT("DA_%s_%s"), *WeaponTypeName, *WeaponTierName);
            FString WeaponDataPath = FString::Printf(TEXT("/Game/Team_4/Sources/WeaponsData/%s/%s.%s"), *WeaponTypeName, *WeaponName, *WeaponName);

            WeaponData = Cast<UWeaponData>(StaticLoadObject(UWeaponData::StaticClass(), nullptr, *WeaponDataPath));
            if (!WeaponData)
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to load WeaponData from path: %s"), *WeaponDataPath);
            }
        }
    }

    CurrentAmmoCount = WeaponData->AmmoCount;
    AmmoCount = CurrentAmmoCount * 3;
    AmmoLimit = AmmoCount;
    UiComponent->SetAmmoText(CurrentAmmoCount, AmmoCount);
    IsShooting = false;
	LastFireTime = 0.0f;
    // Object Pool 초기화
    ProjectilePool = GetWorld()->SpawnActor<AGenericPool>();
    ProjectilePool->InitPool<AProjectile>(10);
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}


FVector UWeaponComponent::GetMuzzleLocation() const
{
    FTransform SocketTransform = SkeletalMeshComponent->GetSocketTransform("Muzzle", RTS_World);
    return SocketTransform.GetLocation();
}

void UWeaponComponent::GetScreenCenterWorldLocationAndDirection(FVector& OutWorldLocation, FVector& OutWorldDirection) const
{
    FVector2D ViewportSize;
    GEngine->GameViewport->GetViewportSize(ViewportSize);
    FVector2D ScreenCenter(ViewportSize.X / 2, ViewportSize.Y / 2);
    UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(GetWorld(), 0), ScreenCenter, OutWorldLocation, OutWorldDirection);
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
    AProjectile* Projectile = ProjectilePool->GetObject<AProjectile>();
    if (Projectile)
    {
        Projectile->Activate();
		Projectile->Initialize(MuzzleLocation, ShootDirection, WeaponData->ProjectileSpeed, WeaponData->Damage);
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

void UWeaponComponent::FireWeapon(bool &IsFire, bool &IsReload)
{
    // HERE: 웨폰 컴포넌트 발사 함수
    if (!GetIsShootable() || IsReload)return;
    IsShooting = true;
    Shoot(IsFire);

    GetWorld()->GetTimerManager().SetTimer(ShootingTimerHandle, FTimerDelegate::CreateLambda([&]
        {
            Shoot(IsFire);
        }
    ), 1.0f / WeaponData->FireRate, true);
}

void UWeaponComponent::StopFireWeapon(bool &IsFire)
{
    IsShooting = false;
    GetWorld()->GetTimerManager().ClearTimer(ShootingTimerHandle); // 타이머 중지
}



void UWeaponComponent::Shoot(bool &IsFire){
    if (CurrentAmmoCount == 0 || !SkeletalMeshComponent || !UiComponent || !IsShooting) return;
    UGameplayStatics::SpawnSoundAttached(FireSound, SkeletalMeshComponent, TEXT("Muzzle"));
    

    FVector WorldLocation;
    FVector WorldDirection;
    GetScreenCenterWorldLocationAndDirection(WorldLocation, WorldDirection);

    FVector Start = WorldLocation;
    FVector End = Start + (WorldDirection * 10000);

    FHitResult HitResult;
    FVector HitLocation = End;
    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility))
    {
        HitLocation = HitResult.Location;
    }

    FVector MuzzleLocation = GetMuzzleLocation();
    FVector ShootDirection = CalculateShootDirection(MuzzleLocation, HitLocation);
    SpawnProjectile(MuzzleLocation, ShootDirection);
    ApplyCameraShake();

    CurrentAmmoCount--;
    UiComponent->SetAmmoText(CurrentAmmoCount, AmmoCount);

	LastFireTime = GetWorld()->GetTimeSeconds();// 마지막 발사시간 갱신


    //애니메이션 Fire Rate 시간 만큼 재생하고 중단시키기
    IsFire = true;
    GetWorld()->GetTimerManager().SetTimer(FireAnimTimerHandle, FTimerDelegate::CreateLambda([&]()
        {
            IsFire = false;
            GetWorld()->GetTimerManager().ClearTimer(FireAnimTimerHandle);
        }), 0.9f / GetFireRate(), false);
}

void UWeaponComponent::ReloadWeapon()
{
    if (IsShooting || AmmoCount == 0)return;

    if (AmmoCount > WeaponData->AmmoCount - CurrentAmmoCount) {
        AmmoCount -= WeaponData->AmmoCount - CurrentAmmoCount;
        CurrentAmmoCount = WeaponData->AmmoCount;
    }
    else {
        CurrentAmmoCount += AmmoCount;
        AmmoCount = 0;
    }

    UiComponent->SetAmmoText(CurrentAmmoCount, AmmoCount);
}

void UWeaponComponent::IncreaseAmmo(const uint32 Ammo)
{
    AmmoCount = FMath::Clamp(AmmoCount + Ammo, 0, AmmoLimit);
    UiComponent->SetAmmoText(CurrentAmmoCount, AmmoCount);
}

bool UWeaponComponent::GetIsShootable() const 
{
    float CurrentTime = GetWorld()->GetTimeSeconds();
    return (CurrentTime - LastFireTime > 1.0f / WeaponData->FireRate) && (CurrentAmmoCount > 0);
}

bool UWeaponComponent::GetIsReloadable() const
{
    return !IsShooting && AmmoCount != 0 && WeaponData->AmmoCount != CurrentAmmoCount;
}
