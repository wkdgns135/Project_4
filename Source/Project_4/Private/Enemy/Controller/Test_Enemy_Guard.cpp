// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/Test_Enemy_Guard.h"
#include "Enemy/Controller/Enemy_FSM.h"
#include "Enemy/EnemyWeapon.h"

ATest_Enemy_Guard::ATest_Enemy_Guard()
{

}

void ATest_Enemy_Guard::InitializeEnemy()
{
   Super::InitializeEnemy();
	maxHp = 100;
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

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	AActor* SpawnActor = GetWorld()->SpawnActor<AEnemyWeapon>(SpawnParams);
	SpawnActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("FX_Trail_02_R"));
	Weapon = Cast<AEnemyWeapon>(SpawnActor);
	Weapon->SetWeaponOwner(this);
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
	Weapon->SetAttackState();
}

void ATest_Enemy_Guard::GetHit(float dmg)
{
	Super::GetHit(dmg);
}

void ATest_Enemy_Guard::Die()
{
	Weapon->Destroy();
	Super::Die();
}

void ATest_Enemy_Guard::DropItem()
{
	Super::DropItem();
}

void ATest_Enemy_Guard::EndAttack()
{
   Super::EndAttack();
   Weapon->EndAttackState();
}


void ATest_Enemy_Guard::SetWeapon() {

}

