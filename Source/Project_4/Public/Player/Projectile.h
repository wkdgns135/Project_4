// Projectile.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "System/PoolableActor.h"
#include "Projectile.generated.h"

UCLASS()
class PROJECT_4_API AProjectile : public APoolableActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AProjectile();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

public:
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	void Activate() override;
	void Deactivate() override;
	void Initialize(const FVector& Location, const FVector& ShootDirection, const uint32 Speed, const uint32 Damage);
    
private:
    class USphereComponent* CollisionComponent;
    class UProjectileMovementComponent* ProjectileMovementComponent;
    class UStaticMeshComponent* ProjectileMeshComponent;
    class UParticleSystem* ImpactEffect;
    class USoundBase* ImpactSound;

    FTimerHandle LifeTimerHandle;
    uint32 Damage;
};

