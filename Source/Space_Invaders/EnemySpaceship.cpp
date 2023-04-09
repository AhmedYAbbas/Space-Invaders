// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpaceship.h"

#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AEnemySpaceship::AEnemySpaceship()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	ProjectileSpawner = CreateDefaultSubobject<USceneComponent>(TEXT("Project Spawner"));
	
	RootComponent = CapsuleComponent;
	StaticMeshComponent->SetupAttachment(RootComponent);
	ProjectileSpawner->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemySpaceship::BeginPlay()
{
	Super::BeginPlay();

	ReadyEnemySpaceships.Init(this, 15);

	StaticMeshComponent->SetGenerateOverlapEvents(true);

	StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemySpaceship::OnHit);

	GetWorldTimerManager().SetTimer(ShootTimeHandle, ReadyEnemySpaceships[Index], &AEnemySpaceship::Shoot, 1.0f, true);
}

// Called every frame
void AEnemySpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector StartLocation = GetActorLocation();
	const FVector EndLocation = GetActorLocation() + LineTraceDistance;
	
	TArray<AActor*> ActorsToIgnore;
	StaticMeshComponent->GetOverlappingActors(ActorsToIgnore);
	
	FHitResult HitResult;
	const bool bHit = UKismetSystemLibrary::LineTraceSingle(this, StartLocation, EndLocation, UEngineTypes::ConvertToTraceType(ECC_Camera), false,
		ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Red, FLinearColor::Green, 0.1f);

	bShoot = !bHit;
	if (bShoot)
	{
		ReadyEnemySpaceships.AddUnique(this);
	}
}

bool AEnemySpaceship::CanShoot() const
{
	return bShoot;
}

void AEnemySpaceship::Shoot()
{
	if (bShoot)
	{
		const FActorSpawnParameters SpawnParameters;
		const FVector Location = ProjectileSpawner->GetComponentLocation();
		const FRotator Rotation = ProjectileSpawner->GetComponentRotation();
		GetWorld()->SpawnActor<AProjectile>(ProjectileToSpawn, Location, Rotation, SpawnParameters);

		Index = FMath::RandRange(0, ReadyEnemySpaceships.Num() - 1);
		GetWorldTimerManager().SetTimer(ShootTimeHandle, ReadyEnemySpaceships[Index], &AEnemySpaceship::Shoot, 1.0f, true);
	}
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
