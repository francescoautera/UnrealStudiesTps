// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerActor.h"

#include "Components/BoxComponent.h"

// Sets default values
ATriggerActor::ATriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    	PrimaryActorTick.bCanEverTick = true;
    	PrimaryActorTick.TickInterval = 0.2f;
    	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("UBoxComponent"));

}

void ATriggerActor::OnTriggerEnter(AActor* overlappedActor, AActor* overlappingActor)
{
	if (overlappingActor->IsA(ACharacter::StaticClass()))
	{
		// OnEnter(overlappedActor, overlappingActor);
		OnActorEnter.Broadcast();
		
	}
}

void ATriggerActor::OnTriggerExit(AActor* overlappedActor, AActor* overlappingActor)
{
	if (overlappingActor->IsA(ACharacter::StaticClass()))
	{
		OnExit(overlappingActor);
		
	}
	
}

void ATriggerActor::CheckCollider()
{
	GetOverlappingActors(ActorSensed, SensedClass);
	for (auto actor : ActorSensed)
	{
		if (!ActorInside.Contains(actor))
		{
			ActorInside.Add(actor);
		}
	}
	auto actors = ActorInside;
	for (auto actor : ActorInside)
	{
		if (!ActorSensed.Contains(actor))
			actors.Remove(actor);
		//OnExit(actor);
	}
	ActorInside = actors;
}

// Called when the game starts or when spawned
void ATriggerActor::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ATriggerActor::OnTriggerEnter);
	OnActorEndOverlap.AddDynamic(this,&ATriggerActor::OnTriggerExit);
	
}

void ATriggerActor::BeginDestroy()
{
	Super::BeginDestroy();
	OnActorBeginOverlap.RemoveDynamic(this, &ATriggerActor::OnTriggerEnter);
	OnActorEndOverlap.RemoveDynamic(this,&ATriggerActor::OnTriggerExit);
}

// Called every frame
void ATriggerActor::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	CheckCollider();

}

void ATriggerActor::TurnOffCollider()
{
	BoxComponent->Activate(false);
}

