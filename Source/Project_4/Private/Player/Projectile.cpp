// Projectile.cpp
#include "Player/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AProjectile::AProjectile()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create and configure a sphere collision component
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    CollisionComponent->InitSphereRadius(15.0f);
    CollisionComponent->SetCollisionProfileName(TEXT("BlockAll"));
    CollisionComponent->SetNotifyRigidBodyCollision(true); // Enable hit events
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
    UE_LOG(LogTemp, Display, TEXT("On hit bullet"));

    if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
    {
        OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
    }

    // Spawn impact effect
    if (ImpactEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
    }

    // Destroy the projectile
    //Destroy();

    Deactivate();
}

void AProjectile::ShootInDirection(const FVector& ShootDirection, const uint32 Speed)
{
    ProjectileMovementComponent->InitialSpeed = Speed;
    ProjectileMovementComponent->MaxSpeed = Speed;
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
	ProjectileMovementComponent->SetActive(true);
}

void AProjectile::Deactivate()
{
    // 액터를 감춤 
    SetActorHiddenInGame(true);
    // 충돌 계산 비활성화
    SetActorEnableCollision(false);
    // 틱(업데이트 함수) 중지 
    SetActorTickEnabled(false);

	ProjectileMovementComponent->SetActive(false);
}
