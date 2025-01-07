// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Notify/AnimNotify_EndDie.h"
#include "Enemy/Controller/Test_Enemy.h"

void UAnimNotify_EndDie::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp)
	{
		//IEnemyAnimationAttackInterface* AttackPawn = Cast<IEnemyAnimationAttackInterface>(MeshComp->GetOwner());
		ATest_Enemy* DeathPawn = Cast<ATest_Enemy>(MeshComp->GetOwner());

		if (DeathPawn)
		{
			DeathPawn->Die();
		}
	}
}
