// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	walkSpeed = 450.0f;
	sprintSpeed = 600.0f;
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CHCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CharacterCamera"));
	CHCameraComponent->SetupAttachment(GetCapsuleComponent());
	CHCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f + BaseEyeHeight));
	CHCameraComponent->bUsePawnControlRotation = true;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext>DEFAULT_CONTEXT(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Team_4/BluePrints/Player/InpuAction/IMC_Player.IMC_Player'"));

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_MOVE(TEXT("/Script/EnhancedInput.InputAction'/Game/Team_4/BluePrints/Player/InpuAction/IA_Move.IA_Move'"));
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_JUMP(TEXT("/Script/EnhancedInput.InputAction'/Game/Team_4/BluePrints/Player/InpuAction/IA_Jump.IA_Jump'"));
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_LOOK(TEXT("/Script/EnhancedInput.InputAction'/Game/Team_4/BluePrints/Player/InpuAction/IA_Look.IA_Look'"));
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_SPRINT(TEXT("/Script/EnhancedInput.InputAction'/Game/Team_4/BluePrints/Player/InpuAction/IA_Sprint.IA_Sprint'"));

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
	}
}

void APlayerCharacter::Jump() {
	Super::Jump();
}
void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// �̵��� ���� ����� �ӵ��� ��Ÿ��
	const FVector2D MovementVector = Value.Get<FVector2D>();
	// �÷��̾��� ���� ����
	const FRotator Rotation = Controller->GetControlRotation();
	// Yaw���� ����� ���ο� ȸ�� ����
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	// Yawȸ���� �������� ���� ���� ���
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// ���� ����� Y��(���� �̵��ӵ�)�� ����Ͽ� �̵�
	AddMovementInput(ForwardDirection, MovementVector.Y);
	// Yawȸ���� �������� ���� ���� ���
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// ���� ����� X��(���� �̵��ӵ�)�� ����Ͽ� �̵�
	AddMovementInput(RightDirection, MovementVector.X);
}
void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// ȸ����
	const FVector2D LookVector = Value.Get<FVector2D>();
	// X��(���� ȸ����)�� ����� yawȸ�� �߰� > ���� �ü� ȸ��
	AddControllerYawInput(LookVector.X);
	// Y��(���� ȸ����)�� ����� pitchȸ�� �߰� > ���� �ü� ȸ��
	AddControllerPitchInput(LookVector.Y);
}
void APlayerCharacter::Sprint() {
	GetCharacterMovement()->MaxWalkSpeed = sprintSpeed;
}
void APlayerCharacter::StopSprint() {
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}



