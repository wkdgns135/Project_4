#include "Enemy/Controller/Enemy_FSM.h"
#include "Enemy/Controller/Test_Enemy.h"

ATest_Enemy::ATest_Enemy()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ATest_EnemyController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	fsm = CreateDefaultSubobject<UEnemy_FSM>(TEXT("FSM"));
}

void ATest_Enemy::InitializeEnemy()
{
	maxHp = 100;
	strength = 10;
	speed = 30.0f;
	attackRange = 500.0f;
	attackRadius = 200.0f;
	sightRange = 1000.0f;
	currentHp = maxHp;

	bEndAttack = true;
	bEndHit = true;

	AnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
}

void ATest_Enemy::BeginPlay()
{
	Super::BeginPlay();
}

void ATest_Enemy::Tick(float DeltaTime)
{
}

void ATest_Enemy::Idle()
{
	if (fsm) fsm->SetIdleState();
}

void ATest_Enemy::Movement()
{
	if (fsm) fsm->SetMoveState();
}

void ATest_Enemy::Attack()
{
	if (fsm) fsm->SetAttackState();
	//적 유형별 클래스인 파생 클래스에서 구현
}

float ATest_Enemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//공격한 엑터가 플레이어인지 판별 필요?
	GetHit(FinalDamage);

	return FinalDamage;
}

void ATest_Enemy::GetHit(float dmg)
{
	if (fsm && currentHp > 0)
	{
		fsm->SetCurrentHp(currentHp -= dmg);
		fsm->SetHitState();
	}
}

void ATest_Enemy::Die() //die animation 끝나면 호출
{
	DropItem();
	Destroy();
}

void ATest_Enemy::DropItem()
{
	//어떤 확률로 무엇을 드랍할지 구현 필요.
}

void ATest_Enemy::SetAttackCheck(bool flag)
{
	bEndAttack = flag;
	if (fsm) fsm->SetEndAttack(bEndAttack);
}

void ATest_Enemy::SetHitCheck(bool flag)
{
	bEndHit = flag;
	if (fsm) fsm->SetEndHit(bEndHit);
}

bool ATest_Enemy::GetAttackCheck()
{
	return bEndAttack;
}

bool ATest_Enemy::GetHitCheck()
{
	return bEndHit;
}

UEnemyAnimInstance* ATest_Enemy::GetEnemyAnimInstance() { return AnimInstance; }
UAnimMontage* ATest_Enemy::GetAttackMontage() { return AttackMontage; }
UAnimMontage* ATest_Enemy::GetHitMontage() { return HitMontage; }
UAnimMontage* ATest_Enemy::GetDieMontage() { return DieMontage; }

void ATest_Enemy::SetMaxHp(int32 hp) { maxHp = hp; }
void ATest_Enemy::SetCurrentHp(int32 hp) { currentHp = hp; }
void ATest_Enemy::SetSpeed(float spd) { speed = spd; }
void ATest_Enemy::SetStrength(int32 str) { strength = str; }
int32 ATest_Enemy::GetMaxHp() { return maxHp; }
int32 ATest_Enemy::GetCurrentHp() { return currentHp; }
float ATest_Enemy::GetSpeed() { return speed; }
int32 ATest_Enemy::GetStrength() { return strength; }


