// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Task/AnimNotify_AttackHitCheck.h"
#include "Enemy/Task/EnemyAnimationAttackInterface.h"

void UAnimNotify_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp)
	{
		IEnemyAnimationAttackInterface* AttackPawn = Cast<IEnemyAnimationAttackInterface>(MeshComp->GetOwner());

		if (AttackPawn)
		{
			AttackPawn->AttackHitCheck();
		}
	}
}
