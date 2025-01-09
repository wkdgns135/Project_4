// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetArea/SupplyHealKitActor.h"


// Sets default values
ASupplyHealKitActor::ASupplyHealKitActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ammo"));

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));

	//if (MeshAsset.Succeeded())
	//{
	//	Sphere->SetStaticMesh(MeshAsset.Object);
	//}

	//SphereMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	//SphereMesh->SetWorldScale3D(FVector(0.7f));
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
void ASupplyHealKitActor::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASupplyHealKitActor::PlayerOverlap);
}

// Called every frame
void ASupplyHealKitActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, 20 * DeltaTime, 0.0f));
}

void ASupplyHealKitActor::InitializeHealKit(ASupplySpawner* Spawner)
{
	Player = Spawner->GetPlayer();
}

void ASupplyHealKitActor::PlayerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		if (OtherActor == Player)
		{
			//TODO: PlayerCharacter의 체력 30퍼센트 증가 구현
			UE_LOG(LogTemp, Warning, TEXT("Supply HealKit to Player"));
			Destroy();
		}
	}
}


