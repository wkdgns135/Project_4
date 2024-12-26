// Fill out your copyright notice in the Description page of Project Settings.


#include "DG_MyActor.h"

// Sets default values
ADG_MyActor::ADG_MyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADG_MyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADG_MyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

