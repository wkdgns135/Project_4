// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "TargetArea.generated.h"

UCLASS()
class PROJECT_4_API ATargetArea : public AActor
{
	GENERATED_BODY()
	
public:	
	ATargetArea();

	UFUNCTION()
	void PlayerBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void PlayerEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	TObjectPtr<class APlayerCharacter> Player;

private:	
	TObjectPtr<class UStaticMeshComponent> BoxMesh;
	class UBoxComponent* BoxCollider;

	bool bIsTrigger;
	float CurrentTime;
	int Gauge;

	void MissionComplete();
};
