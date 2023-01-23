// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Door.h"
#include "EnemyManager.h"
#include "TriggerActor.h"
#include "GameFramework/Actor.h"
#include "RoomManager.generated.h"

UCLASS()
class UNREALSTUDIES_API ARoomManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomManager();

	UFUNCTION(BlueprintImplementableEvent)
	void OnFinishRoom();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category ="RoomComponent")
	ATriggerActor* TriggerActor;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "RoomComponent")
	ADoor * Door;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "RoomComponent")
	AEnemyManager* EnemyManager;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Timer")
	float timerUpdateRoomState;

	float currentTimer;


	UFUNCTION(BlueprintCallable)
	void InitRoom();

	void CheckCompletedRoom();

	bool IsCompleted;

	UFUNCTION(BlueprintCallable)
	ATriggerActor* GetTrigger(){return  TriggerActor;}

	

};
