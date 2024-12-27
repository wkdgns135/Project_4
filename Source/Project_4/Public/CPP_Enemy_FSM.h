// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CPP_Enemy.h"
#include "CPP_DetonateEnemy.h"
#include "CPP_TestPlayer.h"
#include <Kismet/GameplayStatics.h>
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_Enemy_FSM.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	IDLE,
	MOVE,
	ATTACK,
	HIT,
	DIE
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_4_API UCPP_Enemy_FSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCPP_Enemy_FSM();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	EEnemyState mState = EEnemyState::IDLE;

	UPROPERTY(VisibleAnywhere, Category = FSM)
	class ACPP_TestPlayer* target;

	UPROPERTY(VisibleAnywhere, Category = FSM)
	class ACPP_Enemy* me;

	void IdleState();
	void MoveState();
	void AttackState();
	void HitState();
	void DieState();
		
};


