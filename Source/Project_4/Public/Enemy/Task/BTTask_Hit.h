#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Enemy/Controller/Test_Enemy.h"
#include "BTTask_Hit.generated.h"


UCLASS()
class PROJECT_4_API UBTTask_Hit : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_Hit();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& BTC, uint8* NodeMemory);

private:
	UBehaviorTreeComponent* bt_comp;
	ATest_Enemy* Enemy;
};
