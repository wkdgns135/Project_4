// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Task/Test_Target_Point.h"

// Sets default values
ATest_Target_Point::ATest_Target_Point()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATest_Target_Point::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATest_Target_Point::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

