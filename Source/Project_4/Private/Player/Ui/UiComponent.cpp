// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Ui/UiComponent.h"

// Sets default values for this component's properties
UUiComponent::UUiComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UUiComponent::BeginPlay()
{
	Super::BeginPlay();
	if (CrosshairWidgetClass)
	{
		CrosshairWidget = CreateWidget<UUserWidget>(GetWorld(), CrosshairWidgetClass);
		if (CrosshairWidget)
		{
			CrosshairWidget->AddToViewport();
		}
	}
	
    AimSize = 0;
}


// Called every frame
void UUiComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
    UpdateCrosshair(DeltaTime);
}

void UUiComponent::UpdateCrosshair(float DeltaTime)
{
    if (!CrosshairWidget) return;

    // Example: Update crosshair based on actor's velocity
    AActor* Owner = GetOwner();
    if (Owner)
    {
        FVector Velocity = Owner->GetVelocity();
        float Speed = Velocity.Size();

        if (Speed > 100)
        {
            AimSize += Speed * DeltaTime; // 빠르게 증가
        }
        else if (Speed > 0)
        {
            AimSize -= FMath::Clamp(Speed * DeltaTime * 10, 0.0f, AimSize); // 점진적으로 감소
        }
        else
        {
            AimSize -= FMath::Clamp(1000 * DeltaTime, 0.0f, AimSize); // 빠르게 감소
        }

        // 최소 크기 제한
        AimSize = FMath::Max(AimSize, 0.0f);

        // Assume the widget has a method or variable to adjust size
        UFunction* UpdateSizeFunction = CrosshairWidget->FindFunction(FName("UpdateCrosshairSize"));
        if (UpdateSizeFunction)
        {
            struct FUpdateParams
            {
                float NewSize;
            };

            FUpdateParams Params;
            Params.NewSize = AimSize;
            CrosshairWidget->ProcessEvent(UpdateSizeFunction, &Params);
        }
    }
}
