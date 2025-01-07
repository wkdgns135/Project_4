// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Notify/AnimNotify_HitEnd.h"
#include "Enemy/Controller/Test_Enemy.h"

void UAnimNotify_HitEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp)
	{
		//IEnemyAnimationAttackInterface* AttackPawn = Cast<IEnemyAnimationAttackInterface>(MeshComp->GetOwner());
		ATest_Enemy* HitPawn = Cast<ATest_Enemy>(MeshComp->GetOwner());

		if (HitPawn)
		{
			HitPawn->EndHit();
		}
	}
}
