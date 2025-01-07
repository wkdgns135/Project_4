// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyWeapon.generated.h"

UCLASS()
class PROJECT_4_API AEnemyWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyWeapon();

	void SetAttackState();
	void EndAttackState();
	void SetWeaponOwner(ACharacter* Character);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere, Category = "Weapon", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* Weapon;
	class ATest_Enemy* Owner;

	UFUNCTION()
	void OnWeaponOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Result);
};
