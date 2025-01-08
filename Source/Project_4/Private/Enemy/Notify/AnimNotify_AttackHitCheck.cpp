#include "Enemy/Notify/AnimNotify_AttackHitCheck.h"
#include "Enemy/Task/EnemyAnimationAttackInterface.h"
#include "Enemy/Controller/Test_Enemy.h"

void UAnimNotify_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp)
	{
		ATest_Enemy* AttackPawn = Cast<ATest_Enemy>(MeshComp->GetOwner());

		if (AttackPawn)
		{
			AttackPawn->Attack();
		}
	}
}
