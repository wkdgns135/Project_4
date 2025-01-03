// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Anim/EnemyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
   Super::NativeInitializeAnimation();
   ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
   if (IsValid(character)) {
      MovementComponent = character->GetCharacterMovement();
   }
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
   Super::NativeUpdateAnimation(DeltaSeconds);
   if (IsValid(MovementComponent)) {
      Speed = MovementComponent->Velocity.Size();
   }
}

void UEnemyAnimInstance::AnimNotify_OnAttackHitCheck()
{
   OnAttackHitCheck.Broadcast();
}

void UEnemyAnimInstance::AnimNotify_OnAttackEndCheck()
{
   OnAttackEndCheck.Broadcast();
   OnAttackEndCheck.Clear();
   OnAttackHitCheck.Clear();
}