// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_Idle_Task.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_4_API UBT_Idle_Task : public UBTTaskNode
{
	GENERATED_BODY()

public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* nodeMemory);

	
};
