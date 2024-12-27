// Fill out your copyright notice in the Description page of Project Settings.
#include "CPP_Enemy_FSM.h"
#include "CPP_Enemy.h"

// Sets default values
ACPP_Enemy::ACPP_Enemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	fsm = CreateDefaultSubobject<UCPP_Enemy_FSM>(TEXT("FSM"));

	maxHp = 100;
	strength = 10;
	speed = 5.0f;
}

// Called when the game starts or when spawned
void ACPP_Enemy::BeginPlay()
{
	Super::BeginPlay();

	currentHp = maxHp;
	Movement();
}

// Called every frame
void ACPP_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_Enemy::Movement()
{
	fsm->mState = EEnemyState::MOVE;
}

void ACPP_Enemy::Attack()
{
	fsm->mState = EEnemyState::ATTACK;
}

void ACPP_Enemy::Hit(int32 damage, AActor* byWho)
{
	fsm->mState = EEnemyState::HIT;

	currentHp -= damage;
	if (currentHp <= 0)
	{
		currentHp = 0;
	}
}

void ACPP_Enemy::Die()
{
	fsm->mState = EEnemyState::DIE;

}

void ACPP_Enemy::DropItem()
{

}

void ACPP_Enemy::SetMaxHp(int32 hp) { maxHp = hp; }
void ACPP_Enemy::SetCurrentHp(int32 hp) { currentHp = hp; }
void ACPP_Enemy::SetSpeed(double spd) { speed = spd; }
void ACPP_Enemy::SetStrength(int32 str) { strength = str; }
int32 ACPP_Enemy::GetMaxHp() { return maxHp; }
int32 ACPP_Enemy::GetCurrentHp() { return currentHp; }
double ACPP_Enemy::GetSpeed() { return speed; }
int32 ACPP_Enemy::GetStrength() { return strength; }
