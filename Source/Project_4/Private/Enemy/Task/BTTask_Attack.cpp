// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Task/BTTask_Attack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
//#include "AnimIn"

UBTTask_Attack::UBTTask_Attack()
{
   NodeName = TEXT("Attack");
}



EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& BTC, uint8* NodeMemory)
{
   AAIController* AIController = BTC.GetAIOwner();
   if (AIController == nullptr) return EBTNodeResult::Failed;

   ACharacter* ControllingPawn = Cast<ACharacter>(AIController->GetPawn());
   if (ControllingPawn == nullptr) return EBTNodeResult::Failed;

   UAnimInstance* AnimInstance = ControllingPawn->GetMesh()->GetAnimInstance();
   if (AnimInstance == nullptr) return EBTNodeResult::Failed;

   AnimInstance->Montage_Play(AttackMontage);

   AnimInstance->OnMontageEnded.AddDynamic(this, &UBTTask_Attack::OnAttackMontageEnded);

   return EBTNodeResult::InProgress;
}

void UBTTask_Attack::OnAttackMontageEnded(UAnimMontage* montage, bool bInterrupted)
{
   UE_LOG(LogTemp, Log, TEXT("Montage End in Task!!"));
}

