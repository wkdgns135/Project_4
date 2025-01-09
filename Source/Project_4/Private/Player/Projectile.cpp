// Projectile.cpp
#include "Player/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "UObject/ConstructorHelpers.h"
#include "Enemy/Controller/Test_Enemy.h"

// Sets default values
AProjectile::AProjectile()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create and configure a sphere collision component
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    CollisionComponent->InitSphereRadius(15.0f);
    CollisionComponent->SetCollisionProfileName(TEXT("BlockAll"));
    CollisionComponent->SetNotifyRigidBodyCollision(true); // Enable hit events
    CollisionComponent->SetCollisionObjectType(ECC_GameTraceChannel4); // 사용자 정의 채널
    CollisionComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore); // 레이 트레이스 채널 무시
    RootComponent = CollisionComponent;

    // Create and configure a projectile movement component
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
    ProjectileMovementComponent->bRotationFollowsVelocity = true;
    ProjectileMovementComponent->bShouldBounce = true;
    ProjectileMovementComponent->Bounciness = 0.3f;
    ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

    // Create and configure a static mesh component
    ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
    if (Mesh.Succeeded())
    {
        ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
    }
    static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Script/Engine.Material'/Game/Team_4/Sources/Material/M_Bullet.M_Bullet'"));
    if (Material.Succeeded())
    {
        UMaterialInstanceDynamic* ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
        ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
    }
    ProjectileMeshComponent->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.05f));
    ProjectileMeshComponent->SetupAttachment(RootComponent);

    
    static ConstructorHelpers::FObjectFinder<UParticleSystem> Particle(TEXT("'/Game/ParagonMurdock/FX/Particles/Abilities/SpreadShot/FX/P_SpreadShotImpact.P_SpreadShotImpact'"));
	if (Particle.Succeeded())
	{
		ImpactEffect = Particle.Object;
	}

    static ConstructorHelpers::FObjectFinder<USoundBase> Sound(TEXT("/Script/Engine.SoundCue'/Game/Team_4/Sources/Sound/SQ_AR_Projectile.SQ_AR_Projectile'"));
    if (Sound.Succeeded()) {
        ImpactSound = Sound.Object;
    }

    // Bind the OnHit function to the collision component's hit event
    CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
    Super::BeginPlay();
	ProjectileMovementComponent->SetActive(false);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
    {
        OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
    }

    // Spawn impact effect
    if (ImpactEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
    }

    if (ImpactSound) {
        UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, Hit.ImpactPoint);
    }

    if (OtherActor->IsA(ATest_Enemy::StaticClass())) {
        FDamageEvent DamageEvent;
        OtherActor->TakeDamage(Damage, DamageEvent, nullptr, this);
    }
    Deactivate();
}

void AProjectile::Activate()
{
	Super::Activate();

    GetWorld()->GetTimerManager().SetTimer(
        LifeTimerHandle, this, &AProjectile::Deactivate, 5.0f, false
    ); // 발사 후 5초가 지나면 Deactivate
}

void AProjectile::Deactivate()
{
	Super::Deactivate();
    GetWorld()->GetTimerManager().ClearTimer(LifeTimerHandle);
	ProjectileMovementComponent->SetActive(false);
}

void AProjectile::Initialize(const FVector& Location, const FVector& ShootDirection, const uint32 Speed, const uint32 Dmg)
{
    Damage = Dmg;
    SetActorLocation(Location);
    ProjectileMovementComponent->InitialSpeed = Speed;
    ProjectileMovementComponent->MaxSpeed = Speed;
    ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
    ProjectileMovementComponent->SetActive(true);
}
