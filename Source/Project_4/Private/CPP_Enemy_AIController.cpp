#include "CPP_Enemy_AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
//#include "PhysicsNNAnimationCharacter.h"
//#include "PhysicsNNanimationComponent.h"


/*
#include "NavigationSystem.h"
#include "Blueprint.AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
*/

void ACPP_Enemy_AIController::BeginPlay()
{
	Super::BeginPlay();

	BTreeComp = Cast<UBehaviorTreeComponent>(GetBrainComponent());
	if (BTreeComp == nullptr)
	{

	}

	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ACPP_TestPlayer::StaticClass());
	target = Cast<ACPP_TestPlayer>(actor);
	//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	enemy = Cast<ACPP_Enemy>(GetOwner());

	GetBlackboardComponent()->SetValueAsVector("StartLocation", enemy->GetActorLocation());
	GetBlackboardComponent()->SetValueAsVector("TargetLocation", target->GetActorLocation());
}

void ACPP_Enemy_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

