// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyWeapon.h"
#include "PlayerCharacter.h"
#include "Enemy/Controller/Test_Enemy.h"
#include "Enemy/Controller/Test_Player.h"
#include "GameFramework/DamageType.h"

// Sets default values
AEnemyWeapon::AEnemyWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	RootComponent = Weapon;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MObject(TEXT("StaticMesh'/Game/Team_4/Enemy/Enemy_Weapon/Sword.Sword'"));
	if (MObject.Succeeded()) {
		Weapon->SetStaticMesh(MObject.Object);
	}
	Weapon->SetCollisionProfileName(TEXT("EnemyWeapon"));
	Weapon->SetGenerateOverlapEvents(false);
}

// Called when the game starts or when spawned
void AEnemyWeapon::BeginPlay()
{
	Super::BeginPlay();
	auto* mesh = GetComponentByClass<UStaticMeshComponent>();
	if (IsValid(mesh))
	{
		mesh->OnComponentBeginOverlap.AddDynamic(this, &AEnemyWeapon::OnWeaponOverlap);
	}
}


void AEnemyWeapon::SetAttackState()
{
	Weapon->SetGenerateOverlapEvents(true);
	UE_LOG(LogCore, Log, TEXT("Sword Attack!!"));
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyWeapon::EndAttackState, 0.4f);
}

void AEnemyWeapon::EndAttackState()
{
	Weapon->SetGenerateOverlapEvents(false);
	UE_LOG(LogCollision, Log, TEXT("Sword Attack End!!"));
}

void AEnemyWeapon::SetWeaponOwner(ACharacter* Character)
{
    auto Temp = Cast<ATest_Enemy>(Character);
	if (Temp != nullptr) Owner = Temp;
}

void AEnemyWeapon::OnWeaponOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Result)
{
	UE_LOG(LogCore, Log, TEXT("Attack Collison!!"));
	//bool b3 = OtherActor->GetClass()->IsChildOf(ATest_Player::StaticClass());

	if (OtherActor->IsA(ATest_Player::StaticClass()))
	{
		UE_LOG(LogCore, Log, TEXT("Attack Player Collison!!"));
		EndAttackState();
		FDamageEvent DamageEvent;
		OtherActor->TakeDamage(Owner->GetStrength(), DamageEvent, Owner->GetController(), Owner);
	}
	
}


