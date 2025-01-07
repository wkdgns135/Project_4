// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Enemy/Controller/Test_Enemy.h"
#include "BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_4_API UBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_Attack();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& BTC, uint8* NodeMemory);
	
	UPROPERTY(EditAnywhere)
	class UAnimMontage* AttackMontage;

	//bool AttackIsPlaying();
	//UAnimMontage* GetAttackMontage();

private:
	UBehaviorTreeComponent* bt_comp;
	ATest_Enemy* enemy;
	class UEnemyAnimInstance* AnimInstance;

	UFUNCTION()
	void OnAttackEnd(UAnimMontage* montage, bool Inturrupt);

	void OnAttackHit();
};
