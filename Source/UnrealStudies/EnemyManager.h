// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

UENUM()
enum EState
{
	Stealth UMETA(DisplayName = "Stealth"),
	Attack  UMETA(DisplayName = "Attack"), 
	Calm UMETA(DisplayName = "Calm")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStateChanged,TEnumAsByte<EState>,CurrState);

UCLASS()
class UNREALSTUDIES_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();
	
	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> Enemies;

	UPROPERTY(BlueprintAssignable)
	FStateChanged OnStateChanged;
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetAllEnemies(TArray<AActor*> RoomEnemy);


	bool CheckIfPlayerIsStealth();


	bool CheckIfAllEnemyDeath();

	void TryUpdateState();

	UFUNCTION()
	void Init(TArray<AActor*> RoomEnemy);

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category ="Control")
	float TimerUpdateState;

	float CurrentTimer;

	bool IsCompleted;

	UPROPERTY(VisibleAnywhere, Category = "State")
	bool IsInititalizer;
	
	void SetState();

	UPROPERTY(VisibleAnywhere,Category = "State")
	TEnumAsByte<EState> CurState;
	
	TEnumAsByte<EState> PrevState;

	
	
};




