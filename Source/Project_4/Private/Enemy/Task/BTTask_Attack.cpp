// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Task/BTTask_Attack.h"
#include "AIController.h"
#include "Enemy/Anim/EnemyAnimInstance.h"
#include "GameFramework/Character.h"
//#include "AnimIn"

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

   UEnemyAnimInstance* AnimInstance = Cast<UEnemyAnimInstance>(ControllingPawn->GetMesh()->GetAnimInstance());
   if (AnimInstance == nullptr) return EBTNodeResult::Failed;

   AnimInstance->Montage_Play(AttackMontage);
   
   //AnimInstance->OnMontageEnded.AddDynamic(this, &UBTTask_Attack::OnAttackMontageEnded);
   if (!AnimInstance->OnAttackHitCheck.IsBoundToObject(this))
      AnimInstance->OnAttackHitCheck.AddUObject(this, &UBTTask_Attack::OnAttackHit);
   if (!AnimInstance->OnAttackEndCheck.IsBoundToObject(this))
      AnimInstance->OnAttackEndCheck.AddUObject(this, &UBTTask_Attack::OnAttackEnd);

   return EBTNodeResult::InProgress;
}

void UBTTask_Attack::OnAttackHit() {
   UE_LOG(LogTemp, Log, TEXT("Attack hit timing"));
   //TODO : binding Attack
}

void UBTTask_Attack::OnAttackEnd() {
   UE_LOG(LogTemp, Log, TEXT("Attack End!!"));
   FinishLatentTask(*bt_comp, EBTNodeResult::Succeeded);

}

//void UBTTask_Attack::OnAttackMontageEnded(UAnimMontage* montage, bool bInterrupted)
//{
//   UE_LOG(LogTemp, Log, TEXT("Montage End in Task!!"));
//}

