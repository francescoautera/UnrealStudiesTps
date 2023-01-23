// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UStaticMeshComponet"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("UBoxComponent"));
	
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	DeInit();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::Init()
{
	StaticMeshComponent->SetVisibility(true);
	BoxComponent->Activate(true);
	GEngine->AddOnScreenDebugMessage(-1, 5.2f, FColor::Blue, FString("InitDoor"));
}

void ADoor::DeInit()
{
	StaticMeshComponent->SetVisibility(false);
	BoxComponent->Activate(false);
}

