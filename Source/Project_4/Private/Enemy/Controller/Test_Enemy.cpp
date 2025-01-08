#include "Enemy/Controller/Test_Enemy.h"
#include "Enemy/Controller/Enemy_FSM.h"


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

	AnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
}

void ATest_Enemy::BeginPlay()
{
	Super::BeginPlay();
}

void ATest_Enemy::Tick(float DeltaTime)
{
}

void ATest_Enemy::Idle() { if (fsm) fsm->SetIdleState(); }
void ATest_Enemy::Movement(){ }
void ATest_Enemy::Attack(){ 
	UE_LOG(LogTemp, Log, TEXT("GuardAttack in ATest_Enemy"));
}
void ATest_Enemy::GetHit(float dmg) { if (fsm) fsm->SetCurrentHp(currentHp -= dmg); }

float ATest_Enemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//공격한 엑터가 플레이어인지 판별 필요?
	GetHit(FinalDamage);

	return FinalDamage;
}

void ATest_Enemy::Die()
{
	DropItem();
	Destroy();
}

void ATest_Enemy::DropItem()
{
	//어떤 확률로 무엇을 드랍할지 구현 필요.
}

void ATest_Enemy::EndHit() { if (fsm) fsm->EndHitAction(); }
void ATest_Enemy::EndAttack() { if (fsm) fsm->EndAttackAction(); }

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


