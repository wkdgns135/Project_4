// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericPool.generated.h"

UCLASS()
class PROJECT_4_API AGenericPool : public AActor
{
    GENERATED_BODY()
public:
    AGenericPool();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Pool")
    int32 PoolSize;
    TArray<AActor*> ObjectPool;

public:
    template <typename T>
    void InitPool(const int32 Size)
    {
        PoolSize = Size;
        UClass* ObjectClass = T::StaticClass();
        for (int32 i = 0; i < Size; ++i) {
            FActorSpawnParameters SpawnParams;
            SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
            AActor* NewActor = GetWorld()->SpawnActor<AActor>(ObjectClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
			NewActor->SetActorEnableCollision(false);
            NewActor->SetActorHiddenInGame(true);

            ObjectPool.Add(NewActor);
        }
    }

    template <typename T>
    T* GetObject() {
        UClass* ObjectClass = T::StaticClass();
        for (AActor* Object : ObjectPool)
        {
            if (!Object->GetActorEnableCollision())
            {
                Object->SetActorEnableCollision(true);
                Object->SetActorHiddenInGame(false);
                return Cast<T>(Object);
            }
        }

        // Ǯ�� ��� ������ ������Ʈ�� ������ ���� ����
        T* NewObject = GetWorld()->SpawnActor<T>(ObjectClass);
        ObjectPool.Add(NewObject);
        return NewObject;
    }

    template <typename T>
    void ReturnObject(T* Object) {
        Object->SetActorEnableCollision(false);
        Object->SetActorHiddenInGame(true);
        Object->Deactivate();
    }
};
