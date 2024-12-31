// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Player/WeaponData.h"
#include "Components/SkeletalMeshComponent.h"
#include "Player/Ui/UiComponent.h"
#include "WeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_4_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
	USkeletalMeshComponent* SkeletalMeshComponent;
	UUiComponent* UiComponent;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UWeaponData *WeaponData;


	UFUNCTION(BlueprintCallable, Category = "Fire") // For debug
	void FireWeapon();

	void EquipWeapon();
};
