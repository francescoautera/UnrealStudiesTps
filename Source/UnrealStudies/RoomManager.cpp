// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomManager.h"

// Sets default values
ARoomManager::ARoomManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoomManager::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ARoomManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	currentTimer += DeltaTime;
	
	if(!IsCompleted && currentTimer>= timerUpdateRoomState)
	{
		currentTimer=0;
		CheckCompletedRoom();
	}

}

void ARoomManager::InitRoom()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.2f, FColor::Blue, FString("Init"));
	EnemyManager->Init(TriggerActor->GetActorsList());
	Door->Init();
	
}

void ARoomManager::CheckCompletedRoom()
{
	if(EnemyManager-> IsCompleted)
	{
		IsCompleted = true;
		Door->DeInit();
		TriggerActor->TurnOffCollider();
		
	}
		
}


