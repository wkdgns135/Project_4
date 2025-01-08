
#include "Enemy/Controller/Enemy_FSM.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacter.h"

UEnemy_FSM::UEnemy_FSM()
{
	PrimaryComponentTick.bCanEverTick = true;
	bInit = false;
}

void UEnemy_FSM::InitializeFSM(ATest_Enemy* Enemy)
{
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass());
	player = Cast<ACharacter>(actor);
	enemy = Enemy;

	aiController = enemy->GetController<ATest_EnemyController>();
	bEndAttackAnim = true;
	bEndHitAnim = true;
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

		if (SetTargetFocus().Size() <= attackRange)
		{
			SetAttackState();
		}
	}
	
}

void UEnemy_FSM::EndAttackAction()
{
	bEndAttackAnim = true;
	SetMoveState();
}

void UEnemy_FSM::StopAttackAction(float delay)
{
	enemy->GetEnemyAnimInstance()->Montage_Stop(delay, enemy->GetAttackMontage());
	aiController->SetState(eState = EEnemyState::WAIT);
	bEndAttackAnim = true;
}

void UEnemy_FSM::EndHitAction()
{
	bEndHitAnim = true;
	SetMoveState();
}

void UEnemy_FSM::StopHitAction(float delay)
{
	enemy->GetEnemyAnimInstance()->Montage_Stop(delay, enemy->GetHitMontage());
	aiController->SetState(eState = EEnemyState::WAIT);
	bEndHitAnim = true;
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
	if (hp > 0)
	{
		CurrentHp = hp;
		SetHitState();
	}
	else
	{
		CurrentHp = 0;
		SetDieState();
	}
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
	bEndAttackAnim = false;
	eState = EEnemyState::ATTACK;
	aiController->SetState(eState);
}

void UEnemy_FSM::SetHitState()
{
	if (!bEndHitAnim) StopHitAction(0.0f);
	else if (!bEndAttackAnim) StopAttackAction(0.0f);

	bEndHitAnim = false;
	eState = EEnemyState::HIT;
	aiController->SetState(eState);
}

void UEnemy_FSM::SetDieState()
{
	if (!bEndHitAnim) StopHitAction(0.3f);
	else if (!bEndAttackAnim) StopAttackAction(0.0f);

	if (eState != EEnemyState::DIE)
	{
		eState = EEnemyState::DIE;
		aiController->SetState(eState);
	}
}

void UEnemy_FSM::SetWaitState()
{
	eState = EEnemyState::WAIT;
	aiController->SetState(eState);
}

void UEnemy_FSM::SetEndAttack(bool flag)
{
	bEndAttackAnim = flag;
}

void UEnemy_FSM::SetEndHit(bool flag)
{
	bEndHitAnim = flag;
}

bool UEnemy_FSM::GetEndAttack()
{
	return bEndAttackAnim;
}

bool UEnemy_FSM::GetEndHit()
{
	return bEndHitAnim;
}
