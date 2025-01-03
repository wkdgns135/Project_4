// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
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
private:
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* montage, bool bInterrupted);
};
