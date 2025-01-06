// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Ui/InventoryWidget.h"
#include "MainMenuGameMode.generated.h"

UCLASS()
class PROJECT_4_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    UInventoryWidget *InventoryWidget;

    UFUNCTION(BlueprintCallable, Category = "UI")
    void ShowInventory();

private:
    void InitPlayerData();
};
