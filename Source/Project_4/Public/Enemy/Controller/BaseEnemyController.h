// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_4_API ABaseEnemyController : public AAIController
{
	GENERATED_BODY()

	static const FName Key_TargetPlayer;
	static const FName Key_SitePosition;
	static const FName Key_isLineofSight;
	static const FName Key_isInAttackRange;
	static const FName Key_isDead;
	static const FName Key_isHit;
	
	class UBehaviorTree* bt_asset;

public:
	ABaseEnemyController();



	void BeginPlay() override;
	void OnPossess(APawn* pawn) override;

	
};
