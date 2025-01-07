#pragma once

#include "CoreMinimal.h"
#include "Enemy/Controller/Test_Enemy.h"
#include "Test_Enemy_Explosion.generated.h"


UCLASS()
class PROJECT_4_API ATest_Enemy_Explosion : public ATest_Enemy
{
	GENERATED_BODY()
	
public:
	ATest_Enemy_Explosion();

	void InitializeEnemy() override;
	void Idle() override;
	void Movement() override;
	void Attack() override;
	void GetHit(float dmg) override;
	void Die() override;
	void DropItem() override;

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
