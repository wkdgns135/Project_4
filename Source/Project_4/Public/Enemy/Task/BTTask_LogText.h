// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_LogText.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_4_API UBTTask_LogText : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_LogText();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& BTC, uint8* NodeMemory) override;
	
	UPROPERTY(EditAnywhere)
	FString log;
};
