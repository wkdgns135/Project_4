// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TimerManager.h"
#include "BTTask_TestInProgress.generated.h"


/**
 * 
 */
UCLASS()
class PROJECT_4_API UBTTask_TestInProgress : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_TestInProgress();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& BTC, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& BTC, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	float Wait_Time;
	
private:
	FTimerHandle TimerHandler;
};
