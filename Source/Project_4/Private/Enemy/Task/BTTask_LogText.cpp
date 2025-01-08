// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Task/BTTask_LogText.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_LogText::UBTTask_LogText() {
   NodeName = TEXT("LogText");
}

EBTNodeResult::Type UBTTask_LogText::ExecuteTask(UBehaviorTreeComponent& BTC, uint8* NodeMemory) {
   //UE_LOG(LogTemp, Log, TEXT("%s"),*log);
   //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, log);
   FString str = BTC.GetBlackboardComponent()->GetValueAsString(TEXT("TestString"));
   UE_LOG(LogTemp, Log, TEXT("%s"),*str);
   GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, str);
   return EBTNodeResult::Succeeded;
}