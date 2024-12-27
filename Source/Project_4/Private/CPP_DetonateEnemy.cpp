// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_Enemy_FSM.h"
#include "CPP_DetonateEnemy.h"



ACPP_DetonateEnemy::ACPP_DetonateEnemy()
{
	
}

void ACPP_DetonateEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ACPP_DetonateEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPP_DetonateEnemy::Attack()
{
	Super::Attack();
}

void ACPP_DetonateEnemy::Hit(int32 damage, AActor* byWho)
{
	Super::Hit(damage, byWho);

	if (currentHp > 0) return;

	Destroy();
}

void ACPP_DetonateEnemy::Movement()
{
	Super::Movement();
}

void ACPP_DetonateEnemy::Die()
{
	Super::Die();
}

void ACPP_DetonateEnemy::DropItem()
{
	Super::DropItem();
}
