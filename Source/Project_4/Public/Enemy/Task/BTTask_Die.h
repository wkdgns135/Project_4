// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Enemy/Controller/Test_Enemy.h"
#include "BTTask_Die.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_4_API UBTTask_Die : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Die();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& BTC, uint8* NodeMemory);

	UPROPERTY(EditAnywhere)
	UAnimMontage* DieMontage;

private:
	UBehaviorTreeComponent* bt_comp;
	ATest_Enemy* Enemy;

	UFUNCTION()
	void OnDieEnded(UAnimMontage* montage, bool Inturrupt);
};
