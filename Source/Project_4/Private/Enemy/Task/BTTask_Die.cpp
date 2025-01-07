// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Task/BTTask_Die.h"
#include "AIController.h"
#include "Enemy/Anim/EnemyAnimInstance.h"
#include "GameFramework/Character.h"

UBTTask_Die::UBTTask_Die()
{
	NodeName = TEXT("DIE");
}

EBTNodeResult::Type UBTTask_Die::ExecuteTask(UBehaviorTreeComponent& BTC, uint8* NodeMemory)
{
    bt_comp = &BTC;
    AAIController* AIController = BTC.GetAIOwner();
    if (AIController == nullptr) return EBTNodeResult::Failed;

    ACharacter* ControllingPawn = Cast<ACharacter>(AIController->GetPawn());
    if (ControllingPawn == nullptr) return EBTNodeResult::Failed;

    Enemy = Cast<ATest_Enemy>(ControllingPawn);
    /*
    UEnemyAnimInstance* AnimInstance = Cast<UEnemyAnimInstance>(ControllingPawn->GetMesh()->GetAnimInstance());
    if (AnimInstance == nullptr) return EBTNodeResult::Failed;

    AnimInstance->Montage_Play(DieMontage);
    */

    //
    UEnemyAnimInstance* AnimInstance = Enemy->GetEnemyAnimInstance();
    if (AnimInstance == nullptr) return EBTNodeResult::Failed;

    AnimInstance->Montage_Play(Enemy->GetDieMontage());
    //

    if (!AnimInstance->Montage_GetEndedDelegate()->IsBoundToObject(this))
        AnimInstance->OnMontageEnded.AddUniqueDynamic(this, &UBTTask_Die::OnDieEnded);

    return EBTNodeResult::InProgress;
}

void UBTTask_Die::OnDieEnded(UAnimMontage* montage, bool Inturrupt)
{
    UE_LOG(LogTemp, Log, TEXT("DieEnd"));
    Enemy->Die();
    FinishLatentTask(*bt_comp, EBTNodeResult::Succeeded);
}
