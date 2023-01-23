// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorThrowable.h"
#include "HealthComponent.h"
#include "Perception/AISenseConfig_Hearing.h"

// Sets default values
AActorThrowable::AActorThrowable()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AActorThrowable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorThrowable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ManageLifeTime(DeltaTime);
}

void AActorThrowable::Init(FThrowable ThrowableParam, FVector Velocity) {
	Params = ThrowableParam;
	WeaponMesh->SetStaticMesh(Params.WeaponMesh);
	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->SetPhysicsLinearVelocity(Velocity);
	// Now is throwed
	bIsThrowed = true;
	ElapsedTime = 0.0f;
}

void AActorThrowable::ManageLifeTime(float DeltaTime) {
	if (bIsThrowed) {
		ElapsedTime += DeltaTime;
		if (ElapsedTime >= Params.TimeForExplosion) {
			FTransform HitEFXTransform = GetTransform();
			HitEFXTransform.SetScale3D(FVector::OneVector * 5.0f);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Params.HitEFX, HitEFXTransform);
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), Params.SoundEFX, GetActorLocation());
			UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 1.0f, UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			CheckActorInRadius();
			Destroy();
		}
	}
}

void AActorThrowable::CheckActorInRadius() {
	FCollisionQueryParams QueryParams;
	AActor* Myself = Cast<AActor>(this);
	QueryParams.AddIgnoredActor(Myself);

	FCollisionShape CollShape = FCollisionShape::MakeSphere(Params.DamageRadius);
	// The hit result gets populated by the line trace
	TArray<FHitResult> Hit;

	// Raycast out from the camera, only collide with pawns (they are on the ECC_Pawn collision channel)
	FVector Pos = WeaponMesh->GetComponentLocation();
	bool bHit = GetWorld()->SweepMultiByChannel(Hit, Pos, Pos, FQuat::Identity, ECC_Pawn, CollShape, QueryParams);
	// Draw debug sphere with radius
	DrawDebugSphere(GetWorld(), Pos, Params.DamageRadius, 12, FColor::Black, false, 3.5f);

	if (bHit) {
		for (auto& HitActor : Hit) {
			UHealthComponent* ActorHealth = Cast<UHealthComponent>(HitActor.Actor.Get()->FindComponentByClass(UHealthComponent::StaticClass()));
			if (ActorHealth) {
				ActorHealth->GetDamage(Params.Damage);
				GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Green, TEXT("2 - Hit! "+ HitActor.Actor.Get()->GetFullName()));
			}
		}
	}
}
