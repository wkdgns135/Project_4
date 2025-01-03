// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Hit.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_4_API UBTTask_Hit : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_Hit();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& BTC, uint8* NodeMemory);
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* HitMontage;

private:
	UBehaviorTreeComponent* bt_comp;

	UFUNCTION()
	void OnHitEnded(UAnimMontage* montage, bool Inturrupt);
};
