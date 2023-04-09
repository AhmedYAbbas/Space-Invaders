// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCluster.h"

#include "Components/CapsuleComponent.h"

// Sets default values for this component's properties
AEnemyCluster::AEnemyCluster()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = CapsuleComponent;
}


// Called when the game starts
void AEnemyCluster::BeginPlay()
{
	Super::BeginPlay();
	
	CapsuleComponent->SetGenerateOverlapEvents(true);
	CapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCluster::ChangeMovementDirection);
}


// Called every frame
void AEnemyCluster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector MovementOffset = FVector(0, DeltaY * MovingDirection * DeltaTime, 0);
	const FVector CurrentLocation = GetActorLocation();
	SetActorLocation(CurrentLocation + MovementOffset);
}

void AEnemyCluster::ChangeMovementDirection(UPrimitiveComponent* OverlappedComp, AActor* Other,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	MovingDirection *= -1;
	
	// const FVector CurrentLocation = GetActorLocation();
	// SetActorLocation(CurrentLocation + FVector(0, 0, DeltaZ));
}
