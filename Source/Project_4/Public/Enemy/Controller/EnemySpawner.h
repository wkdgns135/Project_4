#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class PROJECT_4_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemySpawner();

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float SpawnTime;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* EnemyBehaviorTree;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APawn> EnemyPawnExplosion;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APawn> EnemyPawnGuard;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
private:
	float CurrentTime;
	void SpawnEnemy();
	void SpawnEnemyExplosion();
	void SpawnEnemyGuard();
};
