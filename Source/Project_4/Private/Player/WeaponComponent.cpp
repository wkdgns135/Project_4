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

}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

void UWeaponComponent::FireWeapon()
{
    if (!SkeletalMeshComponent || !UiComponent) return;
    // ���� ��ġ ��������
    FTransform SocketTransform = SkeletalMeshComponent->GetSocketTransform("Muzzle", RTS_World); // ���� ��ǥ�� ���
    FVector MuzzleLocation = SocketTransform.GetLocation();
    FRotator MuzzleRotation = SocketTransform.GetRotation().Rotator();

    // ȭ�� �߽� ��������
    FVector2D ViewportSize;
    GEngine->GameViewport->GetViewportSize(ViewportSize);
    FVector2D ScreenCenter(ViewportSize.X / 2, ViewportSize.Y / 2);

    // ȭ�� �߽ɿ��� ���� ��ġ�� ���� ��������
    FVector WorldLocation;
    FVector WorldDirection;
    UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(GetWorld(), 0), ScreenCenter, WorldLocation, WorldDirection);

    // ����ĳ��Ʈ ���� ��ġ�� �� ��ġ ����
    FVector Start = WorldLocation;
    FVector End = Start + (WorldDirection * 10000); // ����ĳ��Ʈ ���� ����

    // ����ĳ��Ʈ �浹 ��� ������ ����
    FHitResult HitResult;

    // ����ĳ��Ʈ ����
    FVector HitLocation;
    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility))
    {
        // �浹�� ��ġ ��������
        HitLocation = HitResult.Location;
    }
    else
    {
        // �浹���� �ʾ��� ���, ������ �� ��ġ�� ���
        HitLocation = End;
    }

    // �߻�ü �߻� ���� ����
    FVector ShootDirection = (HitLocation - MuzzleLocation).GetSafeNormal();

    // AimSize�� ����� ���� ������ �߰�
    float AimSize = UiComponent->GetAimSize();
    float RandomConeHalfAngle = FMath::DegreesToRadians(AimSize / 100.0f); // AimSize�� ����� ���� ����
    ShootDirection = FMath::VRandCone(ShootDirection, RandomConeHalfAngle);

    // �߻�ü ���� �� �߻�
    FActorSpawnParameters SpawnParams;
    AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(AProjectile::StaticClass(), MuzzleLocation, ShootDirection.Rotation(), SpawnParams);
    if (Projectile)
    {
        Projectile->ShootInDirection(ShootDirection, WeaponData->ProjectileSpeed);
    }
    
    // ī�޶� ����ũ ����
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController)
    {
        PlayerController->ClientStartCameraShake(UUiCameraShake::StaticClass(), WeaponData->Recoil);

    }

    // ����׿� ����ĳ��Ʈ �ð�ȭ
    FVector DebugEnd = MuzzleLocation + (ShootDirection * 10000); // ����ĳ��Ʈ ���� ����
    DrawDebugLine(GetWorld(), MuzzleLocation, DebugEnd, FColor::Red, false, 1, 0, 1);
}
