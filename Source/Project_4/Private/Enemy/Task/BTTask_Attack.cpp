// Fill out your copyright notice in the Description page of Project Settings.


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

   /*
   AnimInstance = Cast<UEnemyAnimInstance>(ControllingPawn->GetMesh()->GetAnimInstance());
   if (AnimInstance == nullptr) return EBTNodeResult::Failed;

   AnimInstance->Montage_Play(AttackMontage);
   */
   //
   AnimInstance = enemy->GetEnemyAnimInstance();
   if (AnimInstance == nullptr) return EBTNodeResult::Failed;

   enemy->SetAttackCheck(false);
   AnimInstance->Montage_Play(enemy->GetAttackMontage());

   //
   UE_LOG(LogTemp, Warning, TEXT("%s Attack Start"), *enemy->GetName());
   /*
   if (!AnimInstance->OnAttackHitCheck.IsBoundToObject(this))
        AnimInstance->OnAttackHitCheck.AddUObject(this, &UBTTask_Attack::OnAttackHit);
        */
   /*
   if (!AnimInstance->OnAttackEndCheck.IsBoundToObject(this))
      AnimInstance->OnAttackEndCheck.AddUObject(this, &UBTTask_Attack::OnAttackEnd);
      */
   
   if (!AnimInstance->Montage_GetEndedDelegate()->IsBoundToObject(this))
       AnimInstance->OnMontageEnded.AddUniqueDynamic(this, &UBTTask_Attack::OnAttackEnd);
   /*
   if (!AnimInstance->Montage_GetEndedDelegate()->IsBoundToObject(this))
       AnimInstance->OnMontageEnded.AddDynamic(this, &UBTTask_Attack::OnAttackEnd);
       */
   return EBTNodeResult::InProgress;
}

void UBTTask_Attack::OnAttackHit() {
   UE_LOG(LogTemp, Log, TEXT("%s Call Attack() of Enemy class"), *enemy->GetName());
   //TODO : binding Attack
   enemy->Attack();
}

void UBTTask_Attack::OnAttackEnd(UAnimMontage* montage, bool Inturrupt) {
   UE_LOG(LogTemp, Log, TEXT("%s Attack End!!"), *enemy->GetName());
   enemy->SetAttackCheck(true);
   enemy->EndAttack();
   FinishLatentTask(*bt_comp, EBTNodeResult::Succeeded);

}
/*
bool UBTTask_Attack::AttackIsPlaying()
{
    bool result = false;

    if (AnimInstance != nullptr)
    {
        result = AnimInstance->Montage_IsPlaying(AttackMontage);
    }

    return result;
}

UAnimMontage* UBTTask_Attack::GetAttackMontage()
{
    return AttackMontage;
}
*/
//void UBTTask_Attack::OnAttackMontageEnded(UAnimMontage* montage, bool bInterrupted)
//{
//   UE_LOG(LogTemp, Log, TEXT("Montage End in Task!!"));
//}

