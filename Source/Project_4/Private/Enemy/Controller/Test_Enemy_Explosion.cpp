// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/Test_Enemy_Explosion.h"
#include "Enemy/Controller/Enemy_FSM.h"


ATest_Enemy_Explosion::ATest_Enemy_Explosion()
{
	
}

void ATest_Enemy_Explosion::InitializeEnemy()
{
	Super::InitializeEnemy();

	maxHp = 100;
	strength = 100;
	speed = 400.0f;
	attackRange = 100.0f;
	attackRadius = 400.0f;
	sightRange = 2000.0f;
	currentHp = maxHp;

	if (fsm)
	{
		fsm->InitializeFSM(this);
		fsm->SetEnemyType(EEnemyType::EXPLOSION);
		fsm->SetEnemyStatus(sightRange, speed, attackRange, maxHp);
		if (fsm->player) Idle();
	}
}

void ATest_Enemy_Explosion::BeginPlay()
{
	Super::BeginPlay();
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
		if (OutHitResult.GetActor())
		{
			FDamageEvent DamageEvent;
			OutHitResult.GetActor()->TakeDamage(strength, DamageEvent, GetController(), this);
			
			
		}
	}

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			Destroy();
		}), 0.3f, false);
	
#if	ENABLE_DRAW_DEBUG
	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
	float CapsuleHalfHeight = attackRange * 0.5f;
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, attackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);
#endif

}

void ATest_Enemy_Explosion::GetHit(float dmg)
{
	Super::GetHit(dmg);
}

void ATest_Enemy_Explosion::Die()
{
	Super::Die();
}

void ATest_Enemy_Explosion::DropItem()
{
	Super::DropItem();
}
