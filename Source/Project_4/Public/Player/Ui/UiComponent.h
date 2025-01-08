// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Blueprint/UserWidget.h"
#include "CrosshairWidget.h"
#include "AmmoWidget.h"
#include "UiComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_4_API UUiComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UUiComponent();

	// Sets default values for this component's properties
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	float GetAimSize() const { return AimSize; }
	void SetAimSize(float Size) { AimSize = Size; }
	void SetAmmoText(const uint32 CurrentAmmoCount, const uint32 AmmoCount);

	UPROPERTY(EditAnywhere, Category = "UI")
	UCrosshairWidget *CrosshairWidget;

	UPROPERTY(EditAnywhere, Category = "UI")
	UAmmoWidget* AmmoWidget;



private:
	void UpdateCrosshair(float DeltaTime);

	float AimSize;
	float MaxAimSize;
	float MinAimSize;

};
