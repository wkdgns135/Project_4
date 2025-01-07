// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/EnemySpawner.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Enemy/Controller/Test_EnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/Controller/Test_Enemy.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UBehaviorTree>AIBehavior(TEXT("BehaviorTree'/Game/MyAI/BT_BaseEnemy_Test.BT_BaseEnemy_Test'"));
	if (AIBehavior.Succeeded())
	{
		EnemyBehaviorTree = AIBehavior.Object;
	}

	ConstructorHelpers::FClassFinder<APawn>EnemyPawnExplosionClass(TEXT("/Script/Engine.Blueprint'/Game/MyBlueprint/BP_Enemy_Explosion.BP_Enemy_Explosion'"));
	if (EnemyPawnExplosionClass.Class)
	{
		EnemyPawnExplosion = EnemyPawnExplosionClass.Class;
	}

	ConstructorHelpers::FClassFinder<APawn>EnemyPawnGuardClass(TEXT("/Script/Engine.Blueprint'/Game/MyBlueprint/BP_Enemy_Guard.BP_Enemy_Guard'"));
	if (EnemyPawnGuardClass.Class)
	{
		EnemyPawnGuard = EnemyPawnGuardClass.Class;
	}
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	CurrentTime = 0.0f;
}	

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentTime += DeltaTime;

	if (CurrentTime >= SpawnTime)
	{
		SpawnEnemy();
		CurrentTime = 0;
	}
}

void AEnemySpawner::SpawnEnemy()
{
	SpawnEnemyExplosion();
	/*
	EEnemyType EnemyType = (EEnemyType)FMath::RandRange(0, 1);

	switch (EnemyType)
	{
	case EEnemyType::GUARD:
		SpawnEnemyGuard();
		break;

	case EEnemyType::EXPLOSION:
		SpawnEnemyExplosion();
		break;
		
	case EEnemyType::STANDOFF:

		break;

	case EEnemyType::NEAR:

		break;
		
	}
	*/
	
}

void AEnemySpawner::SpawnEnemyExplosion()
{
	AActor* Enemy_Instance = UAIBlueprintHelperLibrary::SpawnAIFromClass(GetWorld(), EnemyPawnExplosion, EnemyBehaviorTree, GetActorLocation(), GetActorRotation(), true);
	ATest_Enemy* EnemyClass = Cast<ATest_Enemy>(Enemy_Instance);
	EnemyClass->GetController<ATest_EnemyController>()->OnBlackboard(EnemyBehaviorTree);
	EnemyClass->InitializeEnemy();
}

void AEnemySpawner::SpawnEnemyGuard()
{
	AActor* Enemy_Instance = UAIBlueprintHelperLibrary::SpawnAIFromClass(GetWorld(), EnemyPawnGuard, EnemyBehaviorTree, GetActorLocation(), GetActorRotation(), true);
	ATest_Enemy* EnemyClass = Cast<ATest_Enemy>(Enemy_Instance);
	EnemyClass->GetController<ATest_EnemyController>()->OnBlackboard(EnemyBehaviorTree);
	EnemyClass->InitializeEnemy();
}
