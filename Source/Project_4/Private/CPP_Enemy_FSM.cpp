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
		IdleState();
		break;

	case EEnemyState::MOVE:
		MoveState();
		break;

	case EEnemyState::ATTACK:
		AttackState();
		break;

	case EEnemyState::HIT:
		HitState();
		break;

	case EEnemyState::DIE:
		DieState();
		break;
	}
}

void UCPP_Enemy_FSM::IdleState()
{
	
}

void UCPP_Enemy_FSM::MoveState()
{
	if (target != nullptr && me != nullptr)
	{
		FVector Direction = target->GetActorLocation() - me->GetActorLocation();

		me->AddMovementInput(Direction.GetSafeNormal());
	}
}

void UCPP_Enemy_FSM::AttackState()
{

}

void UCPP_Enemy_FSM::HitState()
{

}

void UCPP_Enemy_FSM::DieState()
{

}

