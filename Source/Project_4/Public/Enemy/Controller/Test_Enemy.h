#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/DamageEvents.h"
#include "Enemy/Controller/Test_EnemyController.h"
#include "Enemy/Anim/EnemyAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Test_Enemy.generated.h"

UCLASS()
class PROJECT_4_API ATest_Enemy : public ACharacter
{
	GENERATED_BODY()

public:
	ATest_Enemy();

	virtual void InitializeEnemy();
	virtual void Attack();
	virtual void Die();

	void EndHit();
	virtual void EndAttack();

	UEnemyAnimInstance* GetEnemyAnimInstance();
	UAnimMontage* GetAttackMontage();
	UAnimMontage* GetHitMontage();
	UAnimMontage* GetDieMontage();

	void SetMaxHp(int32 hp);
	void SetCurrentHp(int32 hp);
	void SetSpeed(float spd);
	void SetStrength(int32 str);
	int32 GetMaxHp();
	int32 GetCurrentHp();
	float GetSpeed();
	int32 GetStrength();

protected:
	int32 currentHp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSMComponent)
	TObjectPtr<class UEnemy_FSM> fsm;

	UPROPERTY(VisibleAnywhere, Category = "Enemy")
	int32 maxHp;

	UPROPERTY(VisibleAnywhere, Category = "Enemy")
	float speed;

	UPROPERTY(VisibleAnywhere, Category = "Enemy")
	int32 strength;

	UPROPERTY(VisibleAnywhere, Category = "Enemy")
	float attackRange;

	UPROPERTY(VisibleAnywhere, Category = "Enemy")
	float sightRange;

	UPROPERTY(VisibleAnywhere, Category = "Enemy")
	float attackRadius;

	UPROPERTY(EditAnywhere, Category = "Animation")
	TObjectPtr<class UAnimMontage> AttackMontage;

	UPROPERTY(EditAnywhere, Category = "Animation")
	TObjectPtr<class UAnimMontage> HitMontage;

	UPROPERTY(EditAnywhere, Category = "Animation")
	TObjectPtr<class UAnimMontage> DieMontage;

	class UEnemyAnimInstance* AnimInstance;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Idle();
	virtual void Movement();
	virtual void GetHit(float dmg);
	virtual void DropItem();
};
