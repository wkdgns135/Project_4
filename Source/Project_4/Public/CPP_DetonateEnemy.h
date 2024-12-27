// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_Enemy.h"
#include "CPP_DetonateEnemy.generated.h"

UCLASS()
class PROJECT_4_API ACPP_DetonateEnemy : public ACPP_Enemy
{
	GENERATED_BODY()
	
public:
	ACPP_DetonateEnemy();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	void Attack() override;
	void Hit(int32 damage, AActor* byWho) override;
	void Movement() override;
	void DropItem() override;
	void Die() override;
};
