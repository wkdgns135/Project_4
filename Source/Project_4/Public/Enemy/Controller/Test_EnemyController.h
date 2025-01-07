// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Test_EnemyController.generated.h"

UENUM(BlueprintType)
enum class EEnemyType : uint8
{
	GUARD = 0 UMETA(DisplayName = "type_guard"),
	EXPLOSION UMETA(DisplayName = "type_explosion"),
	STANDOFF UMETA(DisplayName = "type_standOff"),
	NEAR UMETA(DisplayName = "type_near")
};

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	WAIT = 0 UMETA(DisplayName = "WAIT"),
	IDLE UMETA(DisplayName = "IDLE"),
	MOVE UMETA(DisplayName = "MOVE"),
	ATTACK UMETA(DisplayName = "ATTACK"),
	HIT UMETA(DisplayName = "HIT"),
	DIE UMETA(DisplayName = "DIE")
};

UCLASS()
class PROJECT_4_API ATest_EnemyController : public AAIController
{
	GENERATED_BODY()
	
	static const FName Key_TargetPlayer;
	static const FName Key_SitePosition;
	static const FName Key_isLineofSight;
	static const FName Key_isInAttackRange;
	static const FName Key_isDead;
	static const FName Key_isHit;
	static const FName Key_eState;
	static const FName Key_eType;
	static const FName Key_TargetLocation;
	static const FName Key_PlayerLocation;

public:
	ATest_EnemyController();

	void BeginPlay() override;
	void OnPossess(APawn* pawn) override;
	void OnBlackboard(UBehaviorTree* bt);

	void SetState(EEnemyState eState);
	void SetType(EEnemyType eType);
	void SetTargetLocation(FVector location);
	void SetPlayerLocation(FVector location);

private:
	//UPROPERTY(VisibleAnywhere, Category = "Enemy")
	//TObjectPtr<class UBehaviorTree> bt_asset;

	UBlackboardComponent* blackBoard;
};
