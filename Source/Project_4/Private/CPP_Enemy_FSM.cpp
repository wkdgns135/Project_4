#include "CPP_Enemy_FSM.h"

UCPP_Enemy_FSM::UCPP_Enemy_FSM()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCPP_Enemy_FSM::BeginPlay()
{
	Super::BeginPlay();

	// ...
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ACPP_TestPlayer::StaticClass());
	target = Cast<ACPP_TestPlayer>(actor);
	
	me = Cast<ACPP_Enemy>(GetOwner());
	hitDelayTime = 1.0f;
}

void UCPP_Enemy_FSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	currentTime += DeltaTime;

	switch (eState)
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

	me->SetActorRotation(newRotation);

	return directionTarget;
}

void UCPP_Enemy_FSM::IdleAction()
{
	//Idle이 아니라 패트롤 구현이 필요함.
}

void UCPP_Enemy_FSM::MoveAction(float DeltaTime)
{
	if (target && me)
	{
		FVector Direction = SetTargetFocus();

		if (Direction.Size() <= attackRange)
		{
			eState = EEnemyState::ATTACK;
		}
		else
		{
			me->AddMovementInput(Direction.GetSafeNormal() * DeltaTime * moveSpeed);
		}
	}
}

void UCPP_Enemy_FSM::AttackAction(float DeltaTime)
{
	if (target && me )
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
			eState = EEnemyState::MOVE;
		}
	}
}

void UCPP_Enemy_FSM::HitAction()
{
	currentTime = 0;

	if (currentTime > hitDelayTime) eState = EEnemyState::MOVE;
}

void UCPP_Enemy_FSM::DieAction()
{
	me->DropItem();
	me->Destroy();
}

void UCPP_Enemy_FSM::SetIdleState()
{
	eState = EEnemyState::IDLE;
}

void UCPP_Enemy_FSM::SetMoveState(float spd, float range)
{
	moveSpeed = spd;
	attackRange = range;
	eState = EEnemyState::MOVE;
}

void UCPP_Enemy_FSM::SetAttackState()
{
	eState = EEnemyState::ATTACK;
}

void UCPP_Enemy_FSM::SetHitState()
{
	eState = EEnemyState::HIT;
}

void UCPP_Enemy_FSM::SetDieState()
{
	eState = EEnemyState::DIE;
}

