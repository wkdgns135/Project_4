// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/Test_Enemy_Guard.h"
#include "Enemy/Controller/Enemy_FSM.h"

ATest_Enemy_Guard::ATest_Enemy_Guard()
{
	maxHp = 300;
	strength = 10;
	speed = 200.0f;
	attackRange = 200.0f;
	sightRange = 2000.0f;
	currentHp = maxHp;


}

void ATest_Enemy_Guard::BeginPlay()
{
	Super::BeginPlay();

	if (fsm)
	{
		fsm->SetEnemyType(EEnemyType::GUARD);
		fsm->SetEnemyStatus(sightRange, speed, attackRange);
		if (fsm->player) Idle();
	}
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

void ATest_Enemy_Guard::GetHit(int32 damage, AActor* byWho)
{
	Super::GetHit(damage, byWho);
}

void ATest_Enemy_Guard::Die()
{
	Super::Die();
}

void ATest_Enemy_Guard::DropItem()
{
	Super::DropItem();
}


