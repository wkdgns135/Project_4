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

    // ���� ��ġ ��������
    FTransform SocketTransform = SkeletalMeshComponent->GetSocketTransform("Muzzle", RTS_World); // ���� ��ǥ�� ���
    FVector MuzzleLocation = SocketTransform.GetLocation();

    // ȭ�� �߽� ��������
    FVector2D ViewportSize;
    GEngine->GameViewport->GetViewportSize(ViewportSize);
    FVector2D ScreenCenter(ViewportSize.X / 2, ViewportSize.Y / 2);

    // ȭ�� �߽ɿ��� ���� ��ġ�� ���� ��������
    FVector WorldLocation;
    FVector WorldDirection;
    UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(GetWorld(), 0), ScreenCenter, WorldLocation, WorldDirection);

    // ����ĳ��Ʈ ���� ��ġ�� �� ��ġ ����
    FVector Start = MuzzleLocation;
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

    // �߻�ü ���� �� �߻� (���� �ڵ�, ���� �߻�ü Ŭ������ ���� ��Ŀ� ���� �ٸ� �� ����)
    FActorSpawnParameters SpawnParams;
    AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileBp, MuzzleLocation, ShootDirection.Rotation(), SpawnParams);
    if (Projectile)
    {
        // �߻�ü�� �ʱ� �ӵ� ���� (���� �ڵ�, ���� �߻�ü Ŭ������ ���� �ٸ� �� ����)
        UProjectileMovementComponent* ProjectileMovement = Projectile->FindComponentByClass<UProjectileMovementComponent>();
        if (ProjectileMovement)
        {
            ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
        }
    }

    // ����׿� ����ĳ��Ʈ �ð�ȭ
    DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1, 0, 1);
}

