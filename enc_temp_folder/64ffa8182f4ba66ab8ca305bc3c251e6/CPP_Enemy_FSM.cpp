// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Enemy_FSM.h"

// Sets default values for this component's properties

UCPP_Enemy_FSM::UCPP_Enemy_FSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCPP_Enemy_FSM::BeginPlay()
{
	Super::BeginPlay();

	// ...
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ACPP_TestPlayer::StaticClass());
	target = Cast<ACPP_TestPlayer>(actor);
	
	me = Cast<ACPP_Enemy>(GetOwner());
	
}


// Called every frame
void UCPP_Enemy_FSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	switch (mState)
	{
	case EEnemyState::IDLE:
		IdleAction();
		break;

	case EEnemyState::MOVE:
		MoveAction(DeltaTime);
		break;

	case EEnemyState::ATTACK:
		AttackAction(DeltaTime);
		break;

	case EEnemyState::HIT:
		HitAction();
		break;

	case EEnemyState::DIE:
		DieAction();
		break;
	}
}

FVector UCPP_Enemy_FSM::SetTargetFocus()
{
	FVector enemyLocation = me->GetActorLocation();
	FVector targetLocation = target->GetActorLocation();

	FVector directionTarget = (targetLocation - enemyLocation);
	directionTarget.Z = 0;

	FRotator newRotation = directionTarget.Rotation();

	//me->SetActorRotation(FRotator(0, newRotation.Yaw, 0));
	me->SetActorRotation(newRotation);

	return directionTarget;
}

void UCPP_Enemy_FSM::IdleAction()
{
	
}

void UCPP_Enemy_FSM::MoveAction(float DeltaTime)
{
	if (target != nullptr && me != nullptr)
	{
		FVector Direction = SetTargetFocus();

		if (Direction.Size() <= attackRange)
		{
			mState = EEnemyState::ATTACK;
		}
		else
		{
			me->AddMovementInput(Direction.GetSafeNormal() * DeltaTime * moveSpeed);
		}
	}
}

void UCPP_Enemy_FSM::AttackAction(float DeltaTime)
{
	if (target != nullptr && me != nullptr)
	{
		FVector Direction = SetTargetFocus();

		if (Direction.Size() <= 100)
		{
			UE_LOG(LogTemp, Warning, TEXT("Attack!"));
			me->AddMovementInput(Direction.GetSafeNormal() * DeltaTime * moveSpeed * 2.0f);
		}
		else if (Direction.Size() <= attackRange)
		{
			UE_LOG(LogTemp, Warning, TEXT("Attack State!"));
			me->AddMovementInput(Direction.GetSafeNormal() * DeltaTime * moveSpeed * 1.5f);
		}
		else
		{
			mState = EEnemyState::MOVE;
		}
	}
}

void UCPP_Enemy_FSM::HitAction()
{

}

void UCPP_Enemy_FSM::DieAction()
{
	delete me;
}

void UCPP_Enemy_FSM::SetIdleState()
{
	mState = EEnemyState::IDLE;
}

void UCPP_Enemy_FSM::SetMoveState(float spd, float range)
{
	moveSpeed = spd;
	attackRange = range;
	mState = EEnemyState::MOVE;
}

void UCPP_Enemy_FSM::SetAttackState()
{
	mState = EEnemyState::ATTACK;
}

void UCPP_Enemy_FSM::SetHitState()
{
	mState = EEnemyState::HIT;
}

void UCPP_Enemy_FSM::SetDieState()
{
	mState = EEnemyState::DIE;
}

