// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/Enemy_Near.h"
#include "Enemy/Controller/Enemy_FSM.h"


AEnemy_Near::AEnemy_Near()
{
	maxHp = 200;
	strength = 50;
	speed = 300.0f;
	attackRange = 150.0f;
	sightRange = 2000.0f;
	currentHp = maxHp;
}

void AEnemy_Near::BeginPlay()
{
	Super::BeginPlay();

	if (fsm)
	{
		fsm->SetEnemyType(EEnemyType::NEAR);
		fsm->SetEnemyStatus(sightRange, speed, attackRange);
		if (fsm->player) Idle();
	}
}

void AEnemy_Near::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy_Near::Idle()
{
	Super::Idle();
}

void AEnemy_Near::Movement()
{
	Super::Movement();
}

void AEnemy_Near::Attack()
{
	Super::Attack();
}

void AEnemy_Near::GetHit(int32 damage, AActor* byWho)
{
	Super::GetHit(damage, byWho);
}

void AEnemy_Near::Die()
{
	Super::Die();
}

void AEnemy_Near::DropItem()
{
	Super::DropItem();
}
