// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/BaseEnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ABaseEnemyController::Key_TargetPlayer = TEXT("TargetPlayer");
const FName ABaseEnemyController::Key_SitePosition = TEXT("SitePosition");
const FName ABaseEnemyController::Key_isLineofSight = TEXT("isLineofSight");
const FName ABaseEnemyController::Key_isInAttackRange = TEXT("isInAttackRange");
const FName ABaseEnemyController::Key_isDead = TEXT("isDead");
const FName ABaseEnemyController::Key_isHit = TEXT("isHit");


ABaseEnemyController::ABaseEnemyController() {
   static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/NoCommit/BT_BaseEnemy.BT_BaseEnemy'"));
   if (BTObject.Succeeded()) {
      UE_LOG(LogTemp, Log, TEXT("BehaviorTree Asset Load Success!"));
      bt_asset = BTObject.Object;
   }
}

void ABaseEnemyController::BeginPlay() {
   Super::BeginPlay();
}

void ABaseEnemyController::OnPossess(APawn* pawn) {
   Super::OnPossess(pawn);
   UBlackboardComponent* blackBoard = Blackboard;
   if (UseBlackboard(bt_asset->GetBlackboardAsset(), blackBoard)) {
      RunBehaviorTree(bt_asset);
   }
   Blackboard->SetValueAsBool(Key_isDead, true);
}