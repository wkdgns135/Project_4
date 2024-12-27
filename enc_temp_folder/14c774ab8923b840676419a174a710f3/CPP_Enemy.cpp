// Fill out your copyright notice in the Description page of Project Settings.
#include "CPP_Enemy_FSM.h"
#include "CPP_Enemy.h"

// Sets default values
ACPP_Enemy::ACPP_Enemy()
{
	PrimaryActorTick.bCanEverTick = true;

	fsm = CreateDefaultSubobject<UCPP_Enemy_FSM>(TEXT("FSM"));
	/*
	boxCollision = CreateDefaultSubobject<UBoxCollisionComponent>(TEXT("BoxCollision"));
	//RootComponent = boxComp;
	
	bodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	//bodyMesh->SetupAttachment(boxComp);
	*/

	maxHp = 100;
	strength = 10;
	speed = 30.0f;
	attackRange = 500.0f;
	currentHp = maxHp;
}

void ACPP_Enemy::BeginPlay()
{
	Super::BeginPlay();

	if (fsm != nullptr && fsm->target != nullptr) Movement();
}

void ACPP_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_Enemy::Movement()
{
	if (fsm != nullptr) fsm->SetMoveState(speed, attackRange);
}

void ACPP_Enemy::Attack()
{
	if (fsm != nullptr) fsm->mState = EEnemyState::ATTACK;
}

void ACPP_Enemy::Hit(int32 damage, AActor* byWho)
{
	if (fsm != nullptr) fsm->mState = EEnemyState::HIT;

	currentHp -= damage;
	if (currentHp <= 0)
	{
		currentHp = 0;
	}
}

void ACPP_Enemy::Die()
{
	if (fsm != nullptr) fsm->mState = EEnemyState::DIE;

}

void ACPP_Enemy::DropItem()
{

}

void ACPP_Enemy::SetMaxHp(int32 hp) { maxHp = hp; }
void ACPP_Enemy::SetCurrentHp(int32 hp) { currentHp = hp; }
void ACPP_Enemy::SetSpeed(float spd) { speed = spd; }
void ACPP_Enemy::SetStrength(int32 str) { strength = str; }
int32 ACPP_Enemy::GetMaxHp() { return maxHp; }
int32 ACPP_Enemy::GetCurrentHp() { return currentHp; }
float ACPP_Enemy::GetSpeed() { return speed; }
int32 ACPP_Enemy::GetStrength() { return strength; }
