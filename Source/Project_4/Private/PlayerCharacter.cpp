// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	walkSpeed = 450.0f;
	sprintSpeed = 600.0f;
	isFire = false;
	isReload = false;
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CHCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CharacterCamera"));
	CHCameraComponent->SetupAttachment(GetCapsuleComponent());
	CHCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f + BaseEyeHeight));
	CHCameraComponent->bUsePawnControlRotation = true;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext>DEFAULT_CONTEXT(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Team_4/BluePrints/Player/InputAction/IMC_Player.IMC_Player'"));

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_MOVE(TEXT("/Script/EnhancedInput.InputAction'/Game/Team_4/BluePrints/Player/InputAction/IA_Move.IA_Move'"));
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_JUMP(TEXT("/Script/EnhancedInput.InputAction'/Game/Team_4/BluePrints/Player/InputAction/IA_Jump.IA_Jump'"));
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_LOOK(TEXT("/Script/EnhancedInput.InputAction'/Game/Team_4/BluePrints/Player/InputAction/IA_Look.IA_Look'"));
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_SPRINT(TEXT("/Script/EnhancedInput.InputAction'/Game/Team_4/BluePrints/Player/InputAction/IA_Sprint.IA_Sprint'"));
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_FIRE(TEXT("/Script/EnhancedInput.InputAction'/Game/Team_4/BluePrints/Player/InputAction/IA_Fire.IA_Fire'"));
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_RELOAD(TEXT("/Script/EnhancedInput.InputAction'/Game/Team_4/BluePrints/Player/InputAction/IA_Reload.IA_Reload'"));

	if (DEFAULT_CONTEXT.Succeeded())
	{
		DefaultMappingContext = DEFAULT_CONTEXT.Object;
	}

	if (IA_MOVE.Succeeded())
	{
		MoveAction = IA_MOVE.Object;
	}

	if (IA_JUMP.Succeeded())
	{
		JumpAction = IA_JUMP.Object;
	}

	if (IA_LOOK.Succeeded())
	{
		LookAction = IA_LOOK.Object;
	}

	if (IA_SPRINT.Succeeded())
	{
		SprintAction = IA_SPRINT.Object;
	}

	if (IA_FIRE.Succeeded())
	{
		FireAction = IA_FIRE.Object;
	}

	if (IA_RELOAD.Succeeded())
	{
		ReloadAction = IA_RELOAD.Object;
	}

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();


	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	WeaponComponent = FindComponentByClass<UWeaponComponent>();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopSprint);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &APlayerCharacter::Fire);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopFire);
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &APlayerCharacter::Reload);
	}
}

void APlayerCharacter::Jump() {
	Super::Jump();
}

void APlayerCharacter::Fire()
{
	if (!WeaponComponent)return;
	WeaponComponent->FireWeapon();
	isFire = true;
}

void APlayerCharacter::StopFire()
{
	if (!WeaponComponent)return;
	WeaponComponent->StopFireWeapon();
	isFire = false;
}

void APlayerCharacter::Reload()
{
	if (!WeaponComponent)return;
	WeaponComponent->ReloadWeapon();
	if (!isReload) {
		isReload = true;
		GetWorld()->GetTimerManager().SetTimer(TimerHandel, this, &APlayerCharacter::ResetReload, 1.0f, false);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// 이동에 사용될 방향과 속도를 나타냄
	const FVector2D MovementVector = Value.Get<FVector2D>();
	// 플레이어의 현재 방향
	const FRotator Rotation = Controller->GetControlRotation();
	// Yaw만을 사용해 새로운 회전 생성
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	// Yaw회전을 기준으로 전방 방향 계산
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// 전방 방향과 Y값(전방 이동속도)을 사용하여 이동
	AddMovementInput(ForwardDirection, MovementVector.Y);
	// Yaw회전을 기준으로 우측 방향 계산
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// 우측 방향과 X값(우측 이동속도)을 사용하여 이동
	AddMovementInput(RightDirection, MovementVector.X);
}
void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// 회전량
	const FVector2D LookVector = Value.Get<FVector2D>();
	// X값(수평 회전량)을 사용해 yaw회전 추가 > 수평 시선 회전
	AddControllerYawInput(LookVector.X);
	// Y값(수직 회전량)을 사용해 pitch회전 추가 > 수직 시선 회전
	AddControllerPitchInput(LookVector.Y);
}
void APlayerCharacter::Sprint() {
	GetCharacterMovement()->MaxWalkSpeed = sprintSpeed;
}
void APlayerCharacter::StopSprint() {
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}
void APlayerCharacter::ResetReload() {
	isReload = false;
}



