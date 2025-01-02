#include "Enemy/Controller/Test_EnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "Enemy/Controller/Enemy_FSM.h"

const FName ATest_EnemyController::Key_TargetPlayer = TEXT("TargetPlayer");
const FName ATest_EnemyController::Key_SitePosition = TEXT("SitePosition");
const FName ATest_EnemyController::Key_isLineofSight = TEXT("isLineofSight");
const FName ATest_EnemyController::Key_isInAttackRange = TEXT("isInAttackRange");
const FName ATest_EnemyController::Key_isDead = TEXT("isDead");
const FName ATest_EnemyController::Key_isHit = TEXT("isHit");
const FName ATest_EnemyController::Key_eState = TEXT("eState");
const FName ATest_EnemyController::Key_eType = TEXT("eType");

ATest_EnemyController::ATest_EnemyController() {
    static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/MyAI/BT_BaseEnemy_Test.BT_BaseEnemy_Test'"));
    if (BTObject.Succeeded()) {
        UE_LOG(LogTemp, Log, TEXT("BehaviorTree Asset Load Success!"));
        bt_asset = BTObject.Object;
        blackBoard = Blackboard;
    }
}

void ATest_EnemyController::BeginPlay() {
    Super::BeginPlay();

}

void ATest_EnemyController::OnPossess(APawn* pawn) {
    Super::OnPossess(pawn);

    //UBlackboardComponent* blackBoard = Blackboard;

    if (UseBlackboard(bt_asset->GetBlackboardAsset(), blackBoard)) {
        RunBehaviorTree(bt_asset);
    }
    //Blackboard->SetValueAsBool(Key_isDead, true);
}

void ATest_EnemyController::SetState(EEnemyState eState)
{
    if (Blackboard) Blackboard->SetValueAsEnum(Key_eState, (uint8)eState);
    UE_LOG(LogTemp, Log, TEXT("FSM Call SetState of EnemyController"));
}

void ATest_EnemyController::SetType(EEnemyType eType)
{
    if (Blackboard) Blackboard->SetValueAsEnum(Key_eType, (uint8)eType);
    UE_LOG(LogTemp, Log, TEXT("FSM Call SetType of EnemyController"));
}
