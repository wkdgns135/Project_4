// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/ShootingComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Player/Projectile.h"

// Sets default values for this component's properties
UShootingComponent::UShootingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UShootingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UShootingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UShootingComponent::Shooting()
{
    USkeletalMeshComponent* SkeletalMeshComponent;
    ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
    SkeletalMeshComponent = OwnerCharacter->GetMesh();

    // 머즐 위치 가져오기
    FTransform SocketTransform = SkeletalMeshComponent->GetSocketTransform("Muzzle", RTS_World); // 월드 좌표계 사용
    FVector MuzzleLocation = SocketTransform.GetLocation();

    // 화면 중심 가져오기
    FVector2D ViewportSize;
    GEngine->GameViewport->GetViewportSize(ViewportSize);
    FVector2D ScreenCenter(ViewportSize.X / 2, ViewportSize.Y / 2);

    // 화면 중심에서 월드 위치와 방향 가져오기
    FVector WorldLocation;
    FVector WorldDirection;
    UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(GetWorld(), 0), ScreenCenter, WorldLocation, WorldDirection);

    // 레이캐스트 시작 위치와 끝 위치 설정
    FVector Start = MuzzleLocation;
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

    // 발사체 생성 및 발사 (예시 코드, 실제 발사체 클래스와 스폰 방식에 따라 다를 수 있음)
    FActorSpawnParameters SpawnParams;
    AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileBp, MuzzleLocation, ShootDirection.Rotation(), SpawnParams);
    if (Projectile)
    {
        // 발사체에 초기 속도 설정 (예시 코드, 실제 발사체 클래스에 따라 다를 수 있음)
        UProjectileMovementComponent* ProjectileMovement = Projectile->FindComponentByClass<UProjectileMovementComponent>();
        if (ProjectileMovement)
        {
            ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
        }
    }

    // 디버그용 레이캐스트 시각화
    DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1, 0, 1);
}

