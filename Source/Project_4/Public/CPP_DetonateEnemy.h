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
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Attack() override;
	virtual void Hit(int32 damage, AActor* byWho) override;
	virtual void Movement() override;
	virtual void DropItem() override;
	virtual void Die() override;
};
