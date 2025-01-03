// Fill out your copyright notice in the Description page of Project Settings.


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

   UEnemyAnimInstance* AnimInstance = Cast<UEnemyAnimInstance>(ControllingPawn->GetMesh()->GetAnimInstance());
   if (AnimInstance == nullptr) return EBTNodeResult::Failed;

   AnimInstance->Montage_Play(HitMontage);

   if (!AnimInstance->Montage_GetEndedDelegate()->IsBoundToObject(this))
      AnimInstance->OnMontageEnded.AddUniqueDynamic(this, &UBTTask_Hit::OnHitEnded);


   return EBTNodeResult::InProgress;
}

void UBTTask_Hit::OnHitEnded(UAnimMontage* montage, bool Inturrupt)
{
   UE_LOG(LogTemp, Log, TEXT("HitEnd"));
   FinishLatentTask(*bt_comp, EBTNodeResult::Succeeded);
}
