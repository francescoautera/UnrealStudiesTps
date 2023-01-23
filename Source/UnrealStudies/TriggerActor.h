// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "TriggerActor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FColliderEvent);
UCLASS()
class UNREALSTUDIES_API ATriggerActor : public AActor
{
	GENERATED_BODY()
public:
	ATriggerActor();	
	
    UPROPERTY(BlueprintAssignable)
    FColliderEvent OnActorEnter;
	UFUNCTION(BlueprintImplementableEvent)
	void OnEnter(AActor* overlappedActor, AActor* overlappingActor);
	UFUNCTION(BlueprintImplementableEvent)
	void OnExit(AActor* overlappingActor);
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UBoxComponent* BoxComponent;
	UFUNCTION()
	void OnTriggerEnter(AActor* overlappedActor, AActor* overlappingActor);
	UFUNCTION()
	void OnTriggerExit(AActor* overlappedActor, AActor* overlappingActor);
	
	void CheckCollider();
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Settings")
	TSubclassOf<AActor> SensedClass= {ACharacter::StaticClass()};
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Settings")
	TArray<AActor*> ActorInside;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Settings")
	TArray<AActor*> ActorSensed;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	TArray<AActor*> GetActorsList(){return ActorInside;}


	void TurnOffCollider();
};
