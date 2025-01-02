// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Task/BT_Idle_Task.h"
#include "NavigationSystem.h"
#include "Enemy/Controller/Test_EnemyController.h"
#include <Kismet/GameplayStatics.h>
#include "Enemy/Task/Test_Target_Point.h"


EBTNodeResult::Type UBT_Idle_Task::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* nodeMemory)
{
	auto Controller = Cast<ATest_EnemyController>(OwnerComp.GetAIOwner());
	auto Enemy = Controller->GetPawn();

	if (Enemy)
	{
		auto targetPoint = UGameplayStatics::GetActorOfClass(GetWorld(), ATest_Target_Point::StaticClass());

		FVector enemyLocation = Enemy->GetActorLocation();
		FVector targetPointLocation = targetPoint->GetActorLocation();

		FVector directionTarget = (targetPointLocation - enemyLocation);
		directionTarget.Z = 0;

		FVector nextLocation = (directionTarget / 5) + enemyLocation;

		Controller->SetTargetLocation(nextLocation);

		
	}
	else return EBTNodeResult::Failed;

	return EBTNodeResult::Succeeded;
}
