// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Throwable.h"
#include "GameFramework/Actor.h"
#include "ActorThrowable.generated.h"

UCLASS()
class UNREALSTUDIES_API AActorThrowable : public AActor
{
	GENERATED_BODY()

	UStaticMeshComponent* WeaponMesh;
	
public:
	AActorThrowable();


private:
	bool bIsThrowed = false;
	float ElapsedTime;
	FThrowable Params;

	void ManageLifeTime(float DeltaTime);

	void CheckActorInRadius();

protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Init(FThrowable ThrowableParam, FVector Velocity);

};
