#include "Enemy/Controller/Test_EnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ATest_EnemyController::Key_TargetPlayer = TEXT("TargetPlayer");
const FName ATest_EnemyController::Key_SitePosition = TEXT("SitePosition");
const FName ATest_EnemyController::Key_isLineofSight = TEXT("isLineofSight");
const FName ATest_EnemyController::Key_isInAttackRange = TEXT("isInAttackRange");
const FName ATest_EnemyController::Key_isDead = TEXT("isDead");
const FName ATest_EnemyController::Key_isHit = TEXT("isHit");

ATest_EnemyController::ATest_EnemyController() {
    static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/MyAI/BT_BaseEnemy_Test.BT_BaseEnemy_Test'"));
    if (BTObject.Succeeded()) {
        UE_LOG(LogTemp, Log, TEXT("BehaviorTree Asset Load Success!"));
        bt_asset = BTObject.Object;
    }
}

void ATest_EnemyController::BeginPlay() {
    Super::BeginPlay();

}

void ATest_EnemyController::OnPossess(APawn* pawn) {
    Super::OnPossess(pawn);
    UBlackboardComponent* blackBoard = Blackboard;
    if (UseBlackboard(bt_asset->GetBlackboardAsset(), blackBoard)) {
        RunBehaviorTree(bt_asset);
    }
    //Blackboard->SetValueAsBool(Key_isDead, true);
}