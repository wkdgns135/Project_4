
#include "Enemy/Controller/Enemy_FSM.h"
#include "GameFramework/CharacterMovementComponent.h"

UEnemy_FSM::UEnemy_FSM()
{
	PrimaryComponentTick.bCanEverTick = true;
	bInit = false;
}

void UEnemy_FSM::InitializeFSM(ATest_Enemy* Enemy)
{
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATest_Player::StaticClass());

	player = Cast<ATest_Player>(actor);

	//enemy = Cast<ATest_Enemy>(GetOwner());
	enemy = Enemy;

	aiController = enemy->GetController<ATest_EnemyController>();
	bEndAttackAnim = true;
	//bEndHitAnim = true;
	bInit = true;
}

void UEnemy_FSM::BeginPlay()
{
	Super::BeginPlay();
}

void UEnemy_FSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bInit)
	{
		switch (eState)
		{
		case EEnemyState::IDLE:
			IdleAction(DeltaTime);
			break;

		case EEnemyState::MOVE:
			MoveAction(DeltaTime);
			break;

		case EEnemyState::ATTACK:
			//AttackAction();
			break;

		case EEnemyState::HIT:
			//HitAction();
			break;

		case EEnemyState::DIE:
			//DieAction();
			break;
		}
	}
}

FVector UEnemy_FSM::SetTargetFocus()
{
	FVector enemyLocation = enemy->GetActorLocation();
	FVector targetLocation = player->GetActorLocation();

	FVector directionTarget = (targetLocation - enemyLocation);
	directionTarget.Z = 0;

	//FRotator newRotation = directionTarget.Rotation();

	//enemy->SetActorRotation(newRotation);

	return directionTarget;
}

void UEnemy_FSM::IdleAction(float DeltaTime)
{
	enemy->GetCharacterMovement()->MaxWalkSpeed = moveSpeed;

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
		enemy->GetCharacterMovement()->MaxWalkSpeed = moveSpeed * 2.0f;

		if (SetTargetFocus().Size() <= attackRange - 50)
		{
			SetAttackState();
		}
	}
	
}

void UEnemy_FSM::AttackAction()
{
	if (player && enemy)
	{
		//if (bEndAttackAnim && SetTargetFocus().Size() >= attackRange) SetMoveState();
		if(SetTargetFocus().Size() >= attackRange + 100) SetMoveState();
	}
}

void UEnemy_FSM::HitAction()
{
	if (CurrentHp <= 0) SetDieState();
	else SetMoveState();
}

void UEnemy_FSM::DieAction()
{
	//SetDieState();
}

void UEnemy_FSM::SetEnemyType(EEnemyType enemyType)
{
	eType = enemyType;
	aiController->SetType(eType);
}

void UEnemy_FSM::SetEnemyStatus(float sightR, float spd, float range, int32 hp)
{
	moveSpeed = spd;
	attackRange = range;
	sightRange = sightR;
	CurrentHp = hp;
}

void UEnemy_FSM::SetCurrentHp(int32 hp)
{
	CurrentHp = hp;
}

void UEnemy_FSM::SetIdleState()
{
	eState = EEnemyState::IDLE;
	aiController->SetState(eState, enemy.GetName());
}

void UEnemy_FSM::SetMoveState()
{
	eState = EEnemyState::MOVE;
	aiController->SetState(eState, enemy.GetName());
}

void UEnemy_FSM::SetAttackState()
{
	//if (!bEndHitAnim) return;
	//SetEndAttack(false);
	eState = EEnemyState::ATTACK;
	aiController->SetState(eState, enemy.GetName());
}

void UEnemy_FSM::SetHitState()
{
	//SetEndHit(false);
	eState = EEnemyState::HIT;
	aiController->SetState(eState, enemy.GetName());
}

void UEnemy_FSM::SetDieState()
{
	eState = EEnemyState::DIE;
	aiController->SetState(eState, enemy.GetName());
}

void UEnemy_FSM::SetWaitState()
{
	eState = EEnemyState::WAIT;
	aiController->SetState(eState, enemy.GetName());
}

void UEnemy_FSM::SetEndAttack(bool flag)
{
	bEndAttackAnim = flag;
}

void UEnemy_FSM::SetEndHit(bool flag)
{
	//bEndHitAnim = flag;
}
