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
    // 머즐 위치 가져오기
    FTransform SocketTransform = SkeletalMeshComponent->GetSocketTransform("Muzzle", RTS_World); // 월드 좌표계 사용
    FVector MuzzleLocation = SocketTransform.GetLocation();
    FRotator MuzzleRotation = SocketTransform.GetRotation().Rotator();

    // 화면 중심 가져오기
    FVector2D ViewportSize;
    GEngine->GameViewport->GetViewportSize(ViewportSize);
    FVector2D ScreenCenter(ViewportSize.X / 2, ViewportSize.Y / 2);

    // 화면 중심에서 월드 위치와 방향 가져오기
    FVector WorldLocation;
    FVector WorldDirection;
    UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(GetWorld(), 0), ScreenCenter, WorldLocation, WorldDirection);

    // 레이캐스트 시작 위치와 끝 위치 설정
    FVector Start = WorldLocation;
    FVector End = Start + (WorldDirection * 10000); // 레이캐스트 길이 설정

    // 레이캐스트 충돌 결과 저장할 변수
    FHitResult HitResult;

    // 레이캐스트 실행
    FVector HitLocation;
    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility))
    {
        // 충돌한 위치 가져오기
        HitLocation = HitResult.Location;
    }
    else
    {
        // 충돌하지 않았을 경우, 레이의 끝 위치를 사용
        HitLocation = End;
    }

    // 발사체 발사 방향 설정
    FVector ShootDirection = (HitLocation - MuzzleLocation).GetSafeNormal();

    // AimSize에 비례한 랜덤 오프셋 추가
    float AimSize = UiComponent->GetAimSize();
    float RandomConeHalfAngle = FMath::DegreesToRadians(AimSize / 100.0f); // AimSize에 비례한 각도 설정
    ShootDirection = FMath::VRandCone(ShootDirection, RandomConeHalfAngle);

    // 발사체 생성 및 발사
    FActorSpawnParameters SpawnParams;
    AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(AProjectile::StaticClass(), MuzzleLocation, ShootDirection.Rotation(), SpawnParams);
    if (Projectile)
    {
        Projectile->ShootInDirection(ShootDirection);
    }
    
    // 카메라 쉐이크 적용
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController)
    {
        PlayerController->ClientStartCameraShake(UUiCameraShake::StaticClass(), WeaponData->Recoil);

    }

    // 디버그용 레이캐스트 시각화
    FVector DebugEnd = MuzzleLocation + (ShootDirection * 10000); // 레이캐스트 길이 설정
    DrawDebugLine(GetWorld(), MuzzleLocation, DebugEnd, FColor::Red, false, 1, 0, 1);
}
