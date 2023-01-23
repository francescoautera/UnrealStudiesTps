// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyManager.h"
#include "GameFramework/Actor.h"
#include "SoundManager.generated.h"

UCLASS()
class UNREALSTUDIES_API ASoundManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundManager();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Sounds")
	TMap<TEnumAsByte<EState>,USoundBase*> StateMusic;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	 virtual  void  BeginDestroy() override; 
	UFUNCTION(BlueprintCallable)
	void PlayMusic(TEnumAsByte<EState> CurrState);
	UFUNCTION(BlueprintCallable)
	void StopMusic();
	UFUNCTION(BlueprintCallable)
	void PlayClip(USoundBase* Clip);
	UFUNCTION(BlueprintCallable)
	void StopClipBoss();

	UAudioComponent* StateAudio;
	UAudioComponent* BossAudio;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<AEnemyManager*> EnemyManagers;

	
	UFUNCTION(BlueprintCallable)
	TArray<AEnemyManager*> GetListEnemies(){return EnemyManagers;}

};
