// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

<<<<<<< Updated upstream
=======
//#include "CPP_Enemy_FSM.h"
>>>>>>> Stashed changes
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPP_Enemy.generated.h"

UCLASS()
class PROJECT_4_API ACPP_Enemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_Enemy();
<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

<<<<<<< Updated upstream
=======
public:
	virtual void Movement();
	virtual void Attack();
	virtual void Hit(int32 damage, AActor* byWho);
	virtual void Die();
	virtual void DropItem();
	void SetMaxHp(int32 hp);
	void SetCurrentHp(int32 hp);
	void SetSpeed(double spd);
	void SetStrength(int32 str);
	int32 GetMaxHp();
	int32 GetCurrentHp();
	double GetSpeed();
	int32 GetStrength();

public :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=FSMComponent)
	class UCPP_Enemy_FSM* fsm;

	UPROPERTY(EditAnywhere)
	int32 maxHp;

	UPROPERTY(EditAnywhere)
	double speed;

	UPROPERTY(EditAnywhere)
	int32 strength;

protected :
	int32 currentHp;
	/*
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USkeletalMeshComponent> SkeletalMeshComponent;
	*/
>>>>>>> Stashed changes
};
