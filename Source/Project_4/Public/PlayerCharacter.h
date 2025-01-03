#pragma once

#include "InputActionValue.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Player/WeaponComponent.h"
#include "PlayerCharacter.generated.h"


UCLASS()
class PROJECT_4_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	// IMC
	UPROPERTY(editanywhere, category = input, meta = (allowprivateaccess = true))
	class UInputMappingContext* DefaultMappingContext;
	// IA_Jump
	UPROPERTY(editanywhere, category = input, meta = (allowprivateaccess = true))
	class UInputAction* JumpAction;
	// IA_Look
	UPROPERTY(editanywhere, category = input, meta = (allowprivateaccess = true))
	class UInputAction* LookAction;
	// IA_Move
	UPROPERTY(editanywhere, category = input, meta = (allowprivateaccess = true))
	class UInputAction* MoveAction;
	UPROPERTY(editanywhere, category = input, meta = (allowprivateaccess = true))
	class UInputAction* SprintAction;

	UPROPERTY(editanywhere, category = input, meta = (allowprivateaccess = true))
	class UInputAction* FireAction;

	UPROPERTY(editanywhere, category = input, meta = (allowprivateaccess = true))
	class UInputAction* ReloadAction;

	UPROPERTY(editanywhere, category = input, meta = (allowprivateaccess = true))
	float walkSpeed;
	UPROPERTY(editanywhere, category = input, meta = (allowprivateaccess = true))
	float sprintSpeed;

	UWeaponComponent *WeaponComponent;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void Sprint();
	void StopSprint();
	void Jump() override;
	void Fire();
	void StopFire();
	void Reload();


	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CHCameraComponent;
};
