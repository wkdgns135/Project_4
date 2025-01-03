// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/Test_Enemy_Explosion.h"
#include "Enemy/Controller/Enemy_FSM.h"


ATest_Enemy_Explosion::ATest_Enemy_Explosion()
{
	maxHp = 100;
	strength = 100;
	speed = 400.0f;
	attackRange = 100.0f;
	attackRadius = 200.0f;
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

void ATest_Enemy_Explosion::AttackHitCheck()
{
	Super::AttackHitCheck();

	UE_LOG(LogTemp, Warning, TEXT("In Attack Hit Check!"));

	FHitResult OutHitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), true, this);

	const FVector Start = GetActorLocation() + GetActorForwardVector() + GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + GetActorForwardVector() * attackRange;
	bool HitDetected = GetWorld()->SweepSingleByChannel
	(
		OutHitResult,
		Start,
		End,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(attackRadius),
		Params
	);

	if (HitDetected)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack!"));
	}
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