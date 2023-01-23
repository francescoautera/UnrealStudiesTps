// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"

#include "Enemy.h"
#include "EnemyAIController.h"
#include "HealthComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	IsCompleted = false;
	IsInititalizer= false;
	CurState = Calm;
	PrevState = Calm;
	
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentTimer += DeltaTime;
	if(CurrentTimer >= TimerUpdateState && !IsCompleted && IsInititalizer)
	{
		SetState();
		CurrentTimer = 0;
	}

}


void AEnemyManager::GetAllEnemies(TArray<AActor*> RoomEnemy)
{

	Enemies = RoomEnemy;
	IsInititalizer = true;
}

bool AEnemyManager::CheckIfPlayerIsStealth()
{
		
	for (auto actor : Enemies)
	{
		AEnemy* Enemy = Cast<AEnemy>(actor);
		if(IsValid(Enemy))
		{
			AEnemyAIController* AIController = Cast<AEnemyAIController>(Enemy->GetController());
			if(IsValid(AIController))
			{
				bool seePlayer = AIController->GetBlackboardComponent()->GetValueAsBool("SeePlayer");
				if(seePlayer)
				{
					return false;
				}
			}
			
		}
	}
	return true;
}

bool AEnemyManager::CheckIfAllEnemyDeath() 
{
	for (auto actor : Enemies)
	{
		AEnemy* Enemy = Cast<AEnemy>(actor);
		if(IsValid(Enemy))
		{
			UHealthComponent* HealthComponent = Enemy->GetHealthComponent();
			if(HealthComponent->Health >0 )
			{
				return false;
			}
			
		}
	}
	return true;
}




void AEnemyManager::SetState()
{
	if (CheckIfAllEnemyDeath())
	{
		CurState = Calm;
		IsCompleted = true;
		
	}
	else
	{
		CurState = CheckIfPlayerIsStealth() ? Stealth : Attack;
	}

	TryUpdateState();
	
		
	//GetSoundBasedOnState(State);
	
}


void AEnemyManager::TryUpdateState()
{
	if(PrevState!=CurState)
	{
		FString val= UEnum::GetValueAsString(CurState);
		GEngine->AddOnScreenDebugMessage(-1, 5.2f, FColor::Blue, val);
		OnStateChanged.Broadcast(CurState);
		PrevState = CurState;
	}
}

void AEnemyManager::Init(TArray<AActor*> RoomEnemy)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.2f, FColor::Blue,FString("InitManager") );
	GetAllEnemies(RoomEnemy);
	CurState = Stealth;
	TryUpdateState();
}





