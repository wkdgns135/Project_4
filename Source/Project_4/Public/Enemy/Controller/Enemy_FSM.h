#pragma once

#include "CoreMinimal.h"
#include "Enemy/Controller/Test_Enemy.h"
#include "Enemy/Controller/Test_Player.h"

#include "Enemy/Controller/Test_EnemyController.h"
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

	void IdleAction(float DeltaTime);
	void MoveAction(float DeltaTime);
	void AttackAction(float DeltaTime);
	void HitAction();
	void DieAction();

	void SetIdleState();
	void SetMoveState();
	void SetAttackState();
	void SetHitState();
	void SetDieState();

	void SetEnemyType(EEnemyType enemyType);
	void SetEnemyStatus(float sightR, float spd, float range);
	void SetAttackPlay(bool isplay);
	FVector SetTargetFocus();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float moveSpeed;
	float sightRange;
	float attackRange;
	float hitDelayTime;
	float currentTime;
	bool isPlay;

	TObjectPtr<class ATest_EnemyController> aiController;
};
