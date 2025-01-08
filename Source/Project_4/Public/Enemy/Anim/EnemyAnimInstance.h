// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheck)
DECLARE_MULTICAST_DELEGATE(OnAttackEndCheck)

/**
 * 
 */
UCLASS()
class PROJECT_4_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override; //animInstance가 초기화될때 실행
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; //update 될 때 실행


	UFUNCTION()
	void AnimNotify_OnAttackHitCheck();
	UFUNCTION()
	void AnimNotify_OnAttackEndCheck();

	UPROPERTY(BlueprintReadOnly)
	class UCharacterMovementComponent* MovementComponent;

	UPROPERTY(BlueprintReadOnly)
	float Speed;

public:
	FOnAttackHitCheck OnAttackHitCheck;
	OnAttackEndCheck OnAttackEndCheck;

};
