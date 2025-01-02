// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/Enemy_StandOff.h"
#include "Enemy/Controller/Enemy_FSM.h"


AEnemy_StandOff::AEnemy_StandOff()
{
	maxHp = 150;
	strength = 30;
	speed = 50.0f;
	attackRange = 1000.0f;
	sightRange = 3000.0f;
	currentHp = maxHp;
}

void AEnemy_StandOff::BeginPlay()
{
	Super::BeginPlay();

	if (fsm)
	{
		fsm->SetEnemyType(EEnemyType::STANDOFF);
		fsm->SetEnemyStatus(sightRange, speed, attackRange);
		if (fsm->player) Idle();
	}
}

void AEnemy_StandOff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy_StandOff::Idle()
{
	Super::Idle();
}

void AEnemy_StandOff::Movement()
{
	Super::Movement();
}

void AEnemy_StandOff::Attack()
{
	Super::Attack();
}

void AEnemy_StandOff::GetHit(int32 damage, AActor* byWho)
{
	Super::GetHit(damage, byWho);
}

void AEnemy_StandOff::Die()
{
	Super::Die();
}

void AEnemy_StandOff::DropItem()
{
	Super::DropItem();
}
