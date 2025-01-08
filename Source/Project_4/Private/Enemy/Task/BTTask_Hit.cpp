#include "Enemy/Task/BTTask_Hit.h"
#include "AIController.h"
#include "Enemy/Anim/EnemyAnimInstance.h"
#include "GameFramework/Character.h"


UBTTask_Hit::UBTTask_Hit()
{
   NodeName = TEXT("HIT");
}

EBTNodeResult::Type UBTTask_Hit::ExecuteTask(UBehaviorTreeComponent& BTC, uint8* NodeMemory)
{
    bt_comp = &BTC;
    AAIController* AIController = BTC.GetAIOwner();
    if (AIController == nullptr) return EBTNodeResult::Failed;

    ACharacter* ControllingPawn = Cast<ACharacter>(AIController->GetPawn());
    if (ControllingPawn == nullptr) return EBTNodeResult::Failed;

    Enemy = Cast<ATest_Enemy>(ControllingPawn);

    UEnemyAnimInstance* AnimInstance = Enemy->GetEnemyAnimInstance();
    if (AnimInstance == nullptr) return EBTNodeResult::Failed;

    AnimInstance->Montage_Play(Enemy->GetHitMontage());
    UE_LOG(LogTemp, Log, TEXT("%s Hit Start"), *Enemy->GetName());

    return EBTNodeResult::InProgress;
}