// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Blueprint/UserWidget.h"
#include "UiComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_4_API UUiComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> CrosshairWidgetClass;
	// Sets default values for this component's properties
	UUiComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UUserWidget* CrosshairWidget;
	void UpdateCrosshair(float DeltaTime);

	float AimSize;
	float MaxAimSize;
	float MinAimSize;

public:
	float GetAimSize() const { return AimSize; }
};
