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
	if (fsm) fsm->SetAttackState();
	//�ӽ� �ڵ�. ���� �����Ÿ� �ȿ� ������ FSM���� ���� ���¿� ����.
	//���� FSM���� ȣ���ϸ� �� ������ ������ �������̵��ϴ� �ڵ� �ʿ�.
}

void ACPP_Enemy::GetHit(int32 damage, AActor* byWho)
{
	//�浹�� ���Ͱ� �������� �Ǻ��Ͽ� �÷��̾��� �������� �Ǻ��ϴ� �ڵ� �ʿ�.
	if (fsm) fsm->SetHitState();

	currentHp -= damage;

	if (currentHp <= 0)
	{
		currentHp = 0;
		Die();
	}
}

void ACPP_Enemy::Die()
{
	if (fsm) fsm->SetDieState();
	//��ü�� �״� ��� (hp 0 �̰ų� ����) ȣ��.
}

void ACPP_Enemy::DropItem()
{
	//������ ���, Ÿ���� ����� ���� �������, Ȯ���� ��� ���� �ʿ�.
}

void ACPP_Enemy::SetMaxHp(int32 hp) { maxHp = hp; }
void ACPP_Enemy::SetCurrentHp(int32 hp) { currentHp = hp; }
void ACPP_Enemy::SetSpeed(float spd) { speed = spd; }
void ACPP_Enemy::SetStrength(int32 str) { strength = str; }
int32 ACPP_Enemy::GetMaxHp() { return maxHp; }
int32 ACPP_Enemy::GetCurrentHp() { return currentHp; }
float ACPP_Enemy::GetSpeed() { return speed; }
int32 ACPP_Enemy::GetStrength() { return strength; }
