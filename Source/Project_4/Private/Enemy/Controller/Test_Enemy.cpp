// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/Controller/Enemy_FSM.h"
#include "Enemy/Controller/Test_Enemy.h"

// Sets default values
ATest_Enemy::ATest_Enemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	fsm = CreateDefaultSubobject<UEnemy_FSM>(TEXT("FSM"));
}

// Called when the game starts or when spawned
void ATest_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
	maxHp = 100;
	strength = 10;
	speed = 30.0f;
	attackRange = 500.0f;
	sightRange = 1000.0f;
	currentHp = maxHp;

	if (fsm && fsm->player) Movement();
	fsm->SetEnemyType(EEnemyType::GUARD);
}

// Called every frame
void ATest_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATest_Enemy::Movement()
{
	if (fsm) fsm->SetMoveState(speed, attackRange);
}

void ATest_Enemy::Attack()
{
	if (fsm) fsm->SetAttackState();
	//임시 코드. 보통 사정거리 안에 들어오면 FSM에서 공격 상태에 돌입.
	//따라서 FSM에서 호출하면 적 유형별 공격을 오버라이딩하는 코드 필요.
}

void ATest_Enemy::GetHit(int32 damage, AActor* byWho)
{
	//충돌한 액터가 무엇인지 판별하여 플레이어의 공격인지 판별하는 코드 필요.
	if (fsm) fsm->SetHitState();

	currentHp -= damage;

	if (currentHp <= 0)
	{
		currentHp = 0;
		Die();
	}
}

void ATest_Enemy::Die()
{
	if (fsm) fsm->SetDieState();
	//객체가 죽는 경우 (hp 0 이거나 자폭) 호출.
}

void ATest_Enemy::DropItem()
{
	//자의적 사망, 타의적 사망에 따라 드랍할지, 확률은 어떤지 구현 필요.
}

void ATest_Enemy::SetMaxHp(int32 hp) { maxHp = hp; }
void ATest_Enemy::SetCurrentHp(int32 hp) { currentHp = hp; }
void ATest_Enemy::SetSpeed(float spd) { speed = spd; }
void ATest_Enemy::SetStrength(int32 str) { strength = str; }
int32 ATest_Enemy::GetMaxHp() { return maxHp; }
int32 ATest_Enemy::GetCurrentHp() { return currentHp; }
float ATest_Enemy::GetSpeed() { return speed; }
int32 ATest_Enemy::GetStrength() { return strength; }


