// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "ShootingComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_4_API UShootingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UShootingComponent();
	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AActor> ProjectileBp;

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void Shooting();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
