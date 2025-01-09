// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetArea/SupplyAmmoActor.h"


// Sets default values
ASupplyAmmoActor::ASupplyAmmoActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ammo"));
	SphereMesh->SetCollisionResponseToAllChannels(ECR_Overlap);
	SphereMesh->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereMesh->SetGenerateOverlapEvents(true);

	SetRootComponent(SphereMesh);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->InitSphereRadius(200.0f);

	SphereComponent->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASupplyAmmoActor::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASupplyAmmoActor::PlayerOverlap);
}

// Called every frame
void ASupplyAmmoActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, 20 * DeltaTime, 0.0f));
}

void ASupplyAmmoActor::InitializeAmmo(ASupplySpawner* Spawner)
{
	Player = Spawner->GetPlayer();
}

void ASupplyAmmoActor::PlayerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		if (OtherActor == Player)
		{
			//TODO: IncreasAmmo()의 매개변수 수정 필요
			//Player->FindComponentByClass<UWeaponComponent>()->IncreaseAmmo();
			UE_LOG(LogTemp, Warning, TEXT("Supply Ammo to Player"));
			Destroy();
		}
	}
}

