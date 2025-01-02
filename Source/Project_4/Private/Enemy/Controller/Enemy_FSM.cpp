
#include "Enemy/Controller/Enemy_FSM.h"

UEnemy_FSM::UEnemy_FSM()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UEnemy_FSM::BeginPlay()
{
	Super::BeginPlay();

	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATest_Player::StaticClass());

	player = Cast<ATest_Player>(actor);

	enemy = Cast<ATest_Enemy>(GetOwner());

	aiController = enemy->GetController<ATest_EnemyController>();

	hitDelayTime = 1.0f;
}


void UEnemy_FSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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

FVector UEnemy_FSM::SetTargetFocus()
{
	FVector enemyLocation = enemy->GetActorLocation();
	FVector targetLocation = player->GetActorLocation();

	FVector directionTarget = (targetLocation - enemyLocation);
	directionTarget.Z = 0;

	FRotator newRotation = directionTarget.Rotation();

	enemy->SetActorRotation(newRotation);

	return directionTarget;
}

void UEnemy_FSM::IdleAction()
{
	//패트롤 구현이 필요함.

	if (player && enemy)
	{
		if (SetTargetFocus().Size() <= sightRange)
		{
			SetMoveState();
		}
	}
}

void UEnemy_FSM::MoveAction(float DeltaTime)
{
	if (player && enemy)
	{
		FVector Direction = SetTargetFocus();

		if (Direction.Size() <= attackRange)
		{
			SetAttackState();
		}
		else
		{
			enemy->AddMovementInput(Direction.GetSafeNormal() * DeltaTime * moveSpeed);
		}
	}
	
}

void UEnemy_FSM::AttackAction(float DeltaTime)
{
	if (player && enemy)
	{
		FVector Direction = SetTargetFocus();

		if (Direction.Size() <= attackRange)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Attack!"));
			enemy->AddMovementInput(Direction.GetSafeNormal() * DeltaTime * moveSpeed * 2.0f);
		}
		else
		{
			SetMoveState();
		}
	}
}

void UEnemy_FSM::HitAction()
{
	SetHitState();
	/*
	currentTime = 0;

	if (currentTime > hitDelayTime) eState = EEnemyState::MOVE;
	*/
}

void UEnemy_FSM::DieAction()
{
	SetDieState();
	//enemy->DropItem();
	//enemy->Destroy();
}

void UEnemy_FSM::SetEnemyType(EEnemyType enemyType)
{
	eType = enemyType;
	aiController->SetType(eType);
}

void UEnemy_FSM::SetEnemyStatus(float sightR, float spd, float range)
{
	moveSpeed = spd;
	attackRange = range;
	sightRange = sightR;
}

void UEnemy_FSM::SetIdleState()
{
	eState = EEnemyState::IDLE;
	aiController->SetState(eState);
}

void UEnemy_FSM::SetMoveState()
{
	eState = EEnemyState::MOVE;
	aiController->SetState(eState);
}

void UEnemy_FSM::SetAttackState()
{
	eState = EEnemyState::ATTACK;
	aiController->SetState(eState);
}

void UEnemy_FSM::SetHitState()
{
	eState = EEnemyState::HIT;
	aiController->SetState(eState);
}

void UEnemy_FSM::SetDieState()
{
	eState = EEnemyState::DIE;
	aiController->SetState(eState);
}
