// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpaceship.h"

#include "EngineUtils.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Engine/BlockingVolume.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AEnemySpaceship::AEnemySpaceship()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	
	RootComponent = CapsuleComponent;
	StaticMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemySpaceship::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComponent->SetGenerateOverlapEvents(true);

	StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	// StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemySpaceship::ChangeMovementDirection);
	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemySpaceship::OnHit);
}

// Called every frame
void AEnemySpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// const float MovementOffset = DeltaY * MovingDirection * DeltaTime;
	// const FVector CurrentLocation = GetActorLocation();
	// SetActorLocation(CurrentLocation + FVector(0, MovementOffset, 0));

	// RootComponent->MoveComponent(FVector(0, MovementOffset, 0), FQuat::Identity, false);
	
	// FVector StartLocation = GetActorLocation();
	// FVector EndLocation = GetActorLocation() + LineTraceDistance;
	// TArray<AActor*> ActorsToIgnore;
	// ActorsToIgnore.Add(this);
	// FHitResult HitResult;
	//
	// UKismetSystemLibrary::LineTraceSingle(this, StartLocation, EndLocation, UEngineTypes::ConvertToTraceType(ECC_Camera), false,
	// 	ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Red, FLinearColor::Green, 0.5f);
}

void AEnemySpaceship::ChangeMovementDirection(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ABlockingVolume>(Other))
	{
		MovingDirection *= -1;
	}

	// for (const AEnemySpaceship* EnemySpaceship : TActorRange<AEnemySpaceship>(GetWorld()))
	// {
	// 	EnemySpaceship->StaticMeshComponent->AddRelativeLocation(DeltaZLocation, false);
	// }
}

void AEnemySpaceship::OnHit(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
                            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AProjectile>(Other))
	{
		GetWorld()->DestroyActor(Other);
		GetWorld()->DestroyActor(this);
	}
}