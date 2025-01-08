// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Task/BT_Move_Task.h"
#include "NavigationSystem.h"
#include "Enemy/Controller/Test_EnemyController.h"
#include "Enemy/Controller/Test_Player.h"
#include "PlayerCharacter.h"
#include <Kismet/GameplayStatics.h>


EBTNodeResult::Type UBT_Move_Task::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* nodeMemory)
{
	auto Controller = Cast<ATest_EnemyController>(OwnerComp.GetAIOwner());
	auto Enemy = Controller->GetPawn();

	if (Enemy)
	{
		auto player = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass());

		FVector enemyLocation = Enemy->GetActorLocation();
		FVector playerLocation = player->GetActorLocation();

		FVector directionTarget = (playerLocation - enemyLocation);
		directionTarget.Z = 0;

		FVector targetLocation = directionTarget + enemyLocation;

		Controller->SetPlayerLocation(playerLocation);
	}
	else return EBTNodeResult::Failed;

	return EBTNodeResult::Succeeded;
}
