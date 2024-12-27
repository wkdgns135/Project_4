#include "CPP_Enemy_FSM.h"
#include "CPP_Enemy.h"

ACPP_Enemy::ACPP_Enemy()
{
	PrimaryActorTick.bCanEverTick = true;

	fsm = CreateDefaultSubobject<UCPP_Enemy_FSM>(TEXT("FSM"));
}

void ACPP_Enemy::BeginPlay()
{
	Super::BeginPlay();

	maxHp = 100;
	strength = 10;
	speed = 30.0f;
	attackRange = 500.0f;
	currentHp = maxHp;

	if (fsm && fsm->target) Movement();
}

void ACPP_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_Enemy::Movement()
{
	if (fsm) fsm->SetMoveState(speed, attackRange);
}

void ACPP_Enemy::Attack()
{
	if (fsm) fsm->mState = EEnemyState::ATTACK;
	//임시 코드. 보통 사정거리 안에 들어오면 FSM에서 공격 상태에 돌입.
	//따라서 FSM에서 호출하면 적 유형별 공격을 오버라이딩하는 코드 필요.
}

void ACPP_Enemy::GetHit(int32 damage, AActor* byWho)
{
	//충돌한 액터가 무엇인지 판별하여 플레이어의 공격인지 판별하는 코드 필요.
	if (fsm) fsm->mState = EEnemyState::HIT;

	currentHp -= damage;

	if (currentHp <= 0)
	{
		currentHp = 0;
		Die();
	}
}

void ACPP_Enemy::Die()
{
	if (fsm) fsm->mState = EEnemyState::DIE;
	//객체가 죽는 경우 (hp 0 이거나 자폭) 호출.
}

void ACPP_Enemy::DropItem()
{
	//자의적 사망, 타의적 사망에 따라 드랍할지, 확률은 어떤지 구현 필요.
}

void ACPP_Enemy::SetMaxHp(int32 hp) { maxHp = hp; }
void ACPP_Enemy::SetCurrentHp(int32 hp) { currentHp = hp; }
void ACPP_Enemy::SetSpeed(float spd) { speed = spd; }
void ACPP_Enemy::SetStrength(int32 str) { strength = str; }
int32 ACPP_Enemy::GetMaxHp() { return maxHp; }
int32 ACPP_Enemy::GetCurrentHp() { return currentHp; }
float ACPP_Enemy::GetSpeed() { return speed; }
int32 ACPP_Enemy::GetStrength() { return strength; }
