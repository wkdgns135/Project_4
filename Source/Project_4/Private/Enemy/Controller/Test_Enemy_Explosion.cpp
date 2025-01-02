// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/Test_Enemy_Explosion.h"
#include "Enemy/Controller/Enemy_FSM.h"


ATest_Enemy_Explosion::ATest_Enemy_Explosion()
{
	maxHp = 100;
	strength = 100;
	speed = 400.0f;
	attackRange = 50.0f;
	sightRange = 2000.0f;
	currentHp = maxHp;
}

void ATest_Enemy_Explosion::BeginPlay()
{
	Super::BeginPlay();
	
	if (fsm)
	{
		fsm->SetEnemyType(EEnemyType::EXPLOSION);
		fsm->SetEnemyStatus(sightRange, speed, attackRange);
		if (fsm->player) Idle();
	}
}

void ATest_Enemy_Explosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATest_Enemy_Explosion::Idle()
{
	Super::Idle();
}

void ATest_Enemy_Explosion::Movement()
{
	Super::Movement();
}

void ATest_Enemy_Explosion::Attack()
{
	Super::Attack();
}

void ATest_Enemy_Explosion::GetHit(int32 damage, AActor* byWho)
{
	Super::GetHit(damage, byWho);
}

void ATest_Enemy_Explosion::Die()
{
	Super::Die();
}

void ATest_Enemy_Explosion::DropItem()
{
	Super::DropItem();
}