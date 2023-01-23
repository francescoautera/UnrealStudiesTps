// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundManager.h"

#include "EnemyManager.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASoundManager::ASoundManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASoundManager::BeginPlay()
{
	Super::BeginPlay();
	StateAudio = UGameplayStatics::CreateSound2D(GetWorld(),*StateMusic.Find(Calm));
	StateAudio ->Play();
	
}

// Called every frame
void ASoundManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASoundManager::BeginDestroy()
{
	Super::BeginDestroy();
	if(StateAudio!=nullptr)
	{
		StateAudio = nullptr;
	}
	if(BossAudio!=nullptr)
	{
		BossAudio = nullptr;
	}
	
}

void ASoundManager::PlayMusic(TEnumAsByte<EState> CurrState)
{
	
	if(StateAudio!=nullptr)
	{
		StateAudio->Stop();
		StateAudio->Sound = *StateMusic.Find(CurrState);
		StateAudio->Play();
	}
}

void ASoundManager::StopMusic()
{
	if(StateAudio!=nullptr)
	{
		StateAudio->Stop();
	}
}

void ASoundManager::PlayClip(USoundBase* Clip)
{
	if(BossAudio == nullptr)
	{
		BossAudio = UGameplayStatics::CreateSound2D(GetWorld(),Clip);
		BossAudio->Play();
		StopMusic();
		return;
	}
	
	if(BossAudio!=nullptr && BossAudio->Sound != Clip)
	{
		BossAudio->Stop();
		BossAudio->Sound = Clip;
		BossAudio->Play();
	}

	
	
}

void ASoundManager::StopClipBoss()
{
	if(BossAudio!=nullptr)
	{
		BossAudio->Stop();
		PlayMusic(Calm);
	}

}

