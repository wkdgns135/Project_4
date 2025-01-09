// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetArea/TargetArea.h"

// Sets default values
ATargetArea::ATargetArea()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TargetArea"));
	BoxMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxCollider->InitBoxExtent(FVector(1000, 1000, 1000));
	BoxCollider->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCollider->SetCollisionResponseToAllChannels(ECR_Overlap);
	BoxCollider->SetGenerateOverlapEvents(true);
	SetRootComponent(BoxCollider);

	bIsTrigger = false;
	CurrentTime = 0.0f;
	Gauge = 0;
}

void ATargetArea::BeginPlay()
{
	Super::BeginPlay();
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ATargetArea::PlayerBeginOverlap);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &ATargetArea::PlayerEndOverlap);

	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass());
	Player = Cast<APlayerCharacter>(actor);
}

void ATargetArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsTrigger && Gauge < 100)
	{
		CurrentTime += DeltaTime;

		if (CurrentTime >= 3.0f)
		{
			Gauge += 1;
			CurrentTime = 0.0f;

			//UE_LOG(LogTemp, Warning, TEXT("The Gauge is %d"), Gauge);

			if (Gauge >= 100)
			{
				MissionComplete();
				//UE_LOG(LogTemp, Warning, TEXT("The Gauge is Full. Mission Complete"));
			}
		}
	}
}

void ATargetArea::MissionComplete()
{
	//TODO: 정보 저장, 메인 화면 돌아가기 구현
}

void ATargetArea::PlayerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		if (OtherActor == Player)
		{
			bIsTrigger = true;
			//UE_LOG(LogTemp, Warning, TEXT("Player Enter Target Area. Continue the gauge"));
		}
	}
}

void ATargetArea::PlayerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndext)
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		if (OtherActor == Player)
		{
			bIsTrigger = false;
			//UE_LOG(LogTemp, Warning, TEXT("Player Exit Target Area. Break the gauge"));
		}
	}
}