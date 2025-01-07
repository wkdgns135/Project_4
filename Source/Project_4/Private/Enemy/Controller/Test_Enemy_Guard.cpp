// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/Test_Enemy_Guard.h"
#include "Enemy/Controller/Enemy_FSM.h"

ATest_Enemy_Guard::ATest_Enemy_Guard()
{

}

void ATest_Enemy_Guard::InitializeEnemy()
{
	maxHp = 300;
	strength = 10;
	speed = 200.0f;
	attackRange = 200.0f;
	sightRange = 2000.0f;
	currentHp = maxHp;

	if (fsm)
	{
		fsm->InitializeFSM(this);
		fsm->SetEnemyType(EEnemyType::GUARD);
		fsm->SetEnemyStatus(sightRange, speed, attackRange, maxHp);
		if (fsm->player) Idle();
	}
}

void ATest_Enemy_Guard::BeginPlay()
{
	Super::BeginPlay();
}

void ATest_Enemy_Guard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATest_Enemy_Guard::Idle()
{
	Super::Idle();
}

void ATest_Enemy_Guard::Movement()
{
	Super::Movement();
}

void ATest_Enemy_Guard::Attack()
{
	Super::Attack();
}

void ATest_Enemy_Guard::GetHit(float dmg)
{
	Super::GetHit(dmg);
}

void ATest_Enemy_Guard::Die()
{
	Super::Die();
}

void ATest_Enemy_Guard::DropItem()
{
	Super::DropItem();
}


