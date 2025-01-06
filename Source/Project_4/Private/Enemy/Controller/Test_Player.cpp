// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/Test_Player.h"

// Sets default values
ATest_Player::ATest_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	currentTime = 0.0f;
}

// Called when the game starts or when spawned
void ATest_Player::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATest_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime += DeltaTime;

	if (currentTime >= AttackInterval)
	{
		TestAttack();
		currentTime = 0.0f;
	}
}

// Called to bind functionality to input
void ATest_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATest_Player::TestAttack()
{
	FHitResult OutHitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Test), true, this);

	const FVector Start = GetActorLocation() + GetActorForwardVector() + GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + GetActorForwardVector() * 5000;
	bool HitDetected = GetWorld()->SweepSingleByChannel
	(
		OutHitResult,
		Start,
		End,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3,
		FCollisionShape::MakeSphere(5000),
		Params
	);

	if (HitDetected)
	{
		if (OutHitResult.GetActor())
		{
			FString name = OutHitResult.GetActor()->GetName();
			UE_LOG(LogTemp, Warning, TEXT("Player Attack to Enemy. Name : %s , Damage : %f"), *name, AttackDmg);
			FDamageEvent DamageEvent;
			OutHitResult.GetActor()->TakeDamage(AttackDmg, DamageEvent, GetController(), this);
		}
	}
}

float ATest_Player::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	UE_LOG(LogTemp, Warning, TEXT("Actor Name : %s Damage : %f"), *GetName(), FinalDamage);
	return FinalDamage;
}

