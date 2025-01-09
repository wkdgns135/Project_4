// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/DropItemActor.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ADropItemActor::ADropItemActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DropItem"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));

	if (MeshAsset.Succeeded())
	{
		Sphere->SetStaticMesh(MeshAsset.Object);
	}

	Sphere->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	Sphere->SetWorldScale3D(FVector(0.7f));
	Sphere->SetCollisionResponseToAllChannels(ECR_Overlap);
	Sphere->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetGenerateOverlapEvents(true);

	SetRootComponent(Sphere);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->InitSphereRadius(200.0f);

	SphereComponent->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Team_4/Item/MI_DropItem.MI_DropItem''"));
	if (Material.Succeeded())
	{
		UMaterialInstanceDynamic* SphereMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, Sphere);
		Sphere->SetMaterial(0, SphereMaterialInstance);
	}

	MapTierColor.Add(EWeaponTier::Normal, COLOR_DARK_GREEN);
	MapTierColor.Add(EWeaponTier::Rare, COLOR_DARK_BLUE);
	MapTierColor.Add(EWeaponTier::Epic, COLOR_DARK_PURPLE);
	MapTierColor.Add(EWeaponTier::Unique, COLOR_DARK_YELLOW);
	MapTierColor.Add(EWeaponTier::Legend, COLOR_DARK_RED);
}

void ADropItemActor::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ADropItemActor::PlayerOverlap);
}

void ADropItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADropItemActor::InitializeDropWeapon(EWeaponTier wTier, EWeaponType wType)
{
	WeaponTier = wTier;
	WeaponType = wType;
	
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass());
	Player = Cast<APlayerCharacter>(actor);

	SetColor();
}

void ADropItemActor::PlayerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		if (OtherActor == Player)
		{
			//Player->GetWeaponTierAndType()
			Destroy();
		}
	}
}

void ADropItemActor::SetColor()
{
	float r = MapTierColor[WeaponTier][0] - '0';
	float g = MapTierColor[WeaponTier][1] - '0';
	float b = MapTierColor[WeaponTier][2] - '0';

	TierColor = FVector(r, g, b);
	
	Sphere->SetVectorParameterValueOnMaterials(TEXT("Color"), TierColor);
}


