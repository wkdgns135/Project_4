#include "Enemy/Notify/AnimNotify_HitEnd.h"
#include "Enemy/Controller/Test_Enemy.h"

void UAnimNotify_HitEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp)
	{
		ATest_Enemy* HitPawn = Cast<ATest_Enemy>(MeshComp->GetOwner());

		if (HitPawn)
		{
			HitPawn->EndHit();
		}
	}
}
