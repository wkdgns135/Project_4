// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Controller/Test_Enemy.h"
#include "Test_Enemy_Guard.generated.h"

UCLASS()
class PROJECT_4_API ATest_Enemy_Guard : public ATest_Enemy
{
	GENERATED_BODY()
	
public:
	ATest_Enemy_Guard();

	void Idle() override;
	void Movement() override;
	void Attack() override;
	void GetHit(int32 damage, AActor* byWho) override;
	void Die() override;
	void DropItem() override;

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
