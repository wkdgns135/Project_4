// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
//#include "PhysicsNNAnimationComponent.h"
#include "CPP_Enemy_AIController.generated.h"

//class APhysicsNNAnimationCharacter;
class UBehaviorTreeComponent;

UCLASS()
class PROJECT_4_API ACPP_Enemy_AIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	//ACPP_Enemy_AIController();

	//APhysicsNNAnimationCharacter* GetControlledCharacter() const { return ControlledCharacter; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;

	UPROPERTY()
	UBehaviorTreeComponent* BTreeComp;

	//UPROPERTY()
	//APhysicsNNAnimationCharacter* ControlledCharacter;

	UPROPERTY()
	class UBlackboardData* BBAsset;

	UPROPERTY(VisibleAnywhere, Category = FSM)
	TObjectPtr<class ACPP_TestPlayer> target;

	UPROPERTY(VisibleAnywhere, Category = FSM)
	TObjectPtr<class ACPP_Enemy> enemy;
};
