// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Task/BTTask_Hit.h"
//#include "Enemy/Task/BTTask_Attack.h"
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
   //Enemy->SetHitCheck(false);
   /*
   UEnemyAnimInstance* AnimInstance = Cast<UEnemyAnimInstance>(ControllingPawn->GetMesh()->GetAnimInstance());
   if (AnimInstance == nullptr) return EBTNodeResult::Failed;

   AnimInstance->Montage_Play(HitMontage);
   */

   //
   UEnemyAnimInstance* AnimInstance = Enemy->GetEnemyAnimInstance();
   if (AnimInstance == nullptr) return EBTNodeResult::Failed;

   /*
   if (!Enemy->GetAttackCheck())
   {
       AnimInstance->Montage_Stop(0.1f, Enemy->GetAttackMontage());
       
       //Enemy->SetAttackCheck(true);

       FTimerHandle TimerHandle;
       GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
           {
               Enemy->SetHitCheck(false);
               AnimInstance->Montage_Play(Enemy->GetHitMontage());
               UE_LOG(LogTemp, Log, TEXT("%s Stop Attack Anim And Play New Hit"), *Enemy->GetName());
               if (!AnimInstance->Montage_GetEndedDelegate()->IsBoundToObject(this))
                   AnimInstance->OnMontageEnded.AddUniqueDynamic(this, &UBTTask_Hit::OnHitEnded);
           }), 0.1f, false);
   }
   else if (!Enemy->GetHitCheck())
   {
       AnimInstance->Montage_Stop(0.0f, Enemy->GetHitMontage());

      // Enemy->SetHitCheck(true);

       if (Enemy->GetCurrentHp() > 0)
       {
           Enemy->SetHitCheck(false);
           AnimInstance->Montage_Play(Enemy->GetHitMontage());
           UE_LOG(LogTemp, Log, TEXT("%s Stop Hit Anim And Play New Hit"), *Enemy->GetName());
           if (!AnimInstance->Montage_GetEndedDelegate()->IsBoundToObject(this))
               AnimInstance->OnMontageEnded.AddUniqueDynamic(this, &UBTTask_Hit::OnHitEnded);
       }
   }
   else*/
   {
       Enemy->SetHitCheck(false);
       AnimInstance->Montage_Play(Enemy->GetHitMontage());
       UE_LOG(LogTemp, Log, TEXT("%s Hit Start"), *Enemy->GetName());
       //
       /*
       if (!AnimInstance->Montage_GetEndedDelegate()->IsBoundToObject(this))
           AnimInstance->OnMontageEnded.AddDynamic(this, &UBTTask_Hit::OnHitEnded);
           */
       /*
       if (!AnimInstance->Montage_GetEndedDelegate()->IsBoundToObject(this))
           AnimInstance->OnMontageEnded.AddUniqueDynamic(this, &UBTTask_Hit::OnHitEnded);
           */
   }

   return EBTNodeResult::InProgress;
}

void UBTTask_Hit::OnHitEnded(UAnimMontage* montage, bool Inturrupt)
{
   UE_LOG(LogTemp, Log, TEXT("%s Hit End"), *Enemy->GetName());
   Enemy->EndHit();
   Enemy->SetHitCheck(true);
   //FinishLatentTask(*bt_comp, EBTNodeResult::Succeeded);
}
