#pragma once

#include "CoreMinimal.h"
#include "Test_Enemy.h"
#include "Test_Player.h"
#include "Test_EnemyController.h"
#include <Kismet/GameplayStatics.h>
#include "Components/ActorComponent.h"
#include "Enemy_FSM.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_4_API UEnemy_FSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEnemy_FSM();

	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = "FSM")
	EEnemyState eState = EEnemyState::IDLE;

	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = "FSM")
	EEnemyType eType = EEnemyType::GUARD;

	UPROPERTY(visibleAnywhere, Category = "FSM")
	TObjectPtr<class ATest_Player> player;

	UPROPERTY(visibleAnywhere, Category = "FSM")
	TObjectPtr<class ATest_Enemy> enemy;

	void IdleAction();
	void MoveAction(float DeltaTime);
	void AttackAction(float DeltaTime);
	void HitAction();
	void DieAction();

	void SetIdleState();
	void SetMoveState(float spd, float range);
	void SetAttackState();
	void SetHitState();
	void SetDieState();

	void SetEnemyType(EEnemyType enemyType);

	FVector SetTargetFocus();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float moveSpeed;
	float attackRange;
	float hitDelayTime;
	float currentTime;

	TObjectPtr<class ATest_EnemyController> aiController;
};
