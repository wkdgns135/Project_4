// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Task/BTTask_TestInProgress.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TestInProgress::UBTTask_TestInProgress()
{
   NodeName = TEXT("TestInProgress");
   bNotifyTick = false; // true로 해야 작동한다.
}

EBTNodeResult::Type UBTTask_TestInProgress::ExecuteTask(UBehaviorTreeComponent& BTC, uint8* NodeMemory)
{
   UE_LOG(LogTemp, Log, TEXT("InProgress~~~"));
   FTimerDelegate TimerCallback;
   TimerCallback.BindLambda([this, &BTC]() {
      FinishLatentTask(BTC, EBTNodeResult::Succeeded);

      });

   BTC.GetWorld()->GetTimerManager().SetTimer(TimerHandler, TimerCallback, Wait_Time, false);
   return EBTNodeResult::InProgress;
}

void UBTTask_TestInProgress::TickTask(UBehaviorTreeComponent& BTC, uint8* NodeMemory, float DeltaSeconds) {
   if (BTC.GetBlackboardComponent()->GetValueAsBool(TEXT("isHit")))
   {
      FinishLatentTask(BTC, EBTNodeResult::Succeeded);
   }
}
