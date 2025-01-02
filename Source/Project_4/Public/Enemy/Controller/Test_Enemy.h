// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Enemy/Controller/Enemy_FSM.h"
#include "GameFramework/Character.h"
#include "Test_Enemy.generated.h"

UCLASS()
class PROJECT_4_API ATest_Enemy : public ACharacter
{
	GENERATED_BODY()

public:
	ATest_Enemy();

	virtual void Movement();
	virtual void Attack();
	virtual void GetHit(int32 damage, AActor* byWho);
	virtual void Die();
	virtual void DropItem();
	void SetMaxHp(int32 hp);
	void SetCurrentHp(int32 hp);
	void SetSpeed(float spd);
	void SetStrength(int32 str);
	int32 GetMaxHp();
	int32 GetCurrentHp();
	float GetSpeed();
	int32 GetStrength();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSMComponent)
	TObjectPtr<class UEnemy_FSM> fsm;

	UPROPERTY(EditAnywhere)
	int32 maxHp;

	UPROPERTY(EditAnywhere)
	float speed;

	UPROPERTY(EditAnywhere)
	int32 strength;

	UPROPERTY(EditAnywhere)
	float attackRange;

protected:
	virtual void BeginPlay() override;

	int32 currentHp;

public:	
	virtual void Tick(float DeltaTime) override;

};
