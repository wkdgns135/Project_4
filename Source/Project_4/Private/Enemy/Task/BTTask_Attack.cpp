#include "Enemy/Task/BTTask_Attack.h"
#include "AIController.h"
#include "Enemy/Anim/EnemyAnimInstance.h"
#include "GameFramework/Character.h"

UBTTask_Attack::UBTTask_Attack()
{
   NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& BTC, uint8* NodeMemory)
{
   bt_comp = &BTC;
   AAIController* AIController = BTC.GetAIOwner();
   if (AIController == nullptr) return EBTNodeResult::Failed;

   ACharacter* ControllingPawn = Cast<ACharacter>(AIController->GetPawn());
   if (ControllingPawn == nullptr) return EBTNodeResult::Failed;
   enemy = Cast<ATest_Enemy>(ControllingPawn);

   AnimInstance = enemy->GetEnemyAnimInstance();
   if (AnimInstance == nullptr) return EBTNodeResult::Failed;

   AnimInstance->Montage_Play(enemy->GetAttackMontage());

   return EBTNodeResult::InProgress;
}

