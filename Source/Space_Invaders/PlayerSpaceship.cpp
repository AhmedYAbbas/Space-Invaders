// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpaceship.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Projectile.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APlayerSpaceship::APlayerSpaceship()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	ProjectSpawner = CreateDefaultSubobject<USceneComponent>(TEXT("Project Spawner"));

	RootComponent = CameraComponent;
	GetCapsuleComponent()->SetupAttachment(RootComponent);
	StaticMeshComponent->SetupAttachment(GetCapsuleComponent());
	ProjectSpawner->SetupAttachment(StaticMeshComponent);
}

// Called when the game starts or when spawned
void APlayerSpaceship::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			EnhancedInputSubsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

// Called every frame
void APlayerSpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}	

// Called to bind functionality to input
void APlayerSpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerSpaceship::Move);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &APlayerSpaceship::Shoot);
	}
}

void APlayerSpaceship::Move(const FInputActionValue& Value)
{
	const float DirectionValue = Value.Get<float>();
	AddMovementInput(GetActorRightVector(), DirectionValue);
}

void APlayerSpaceship::Shoot()
{
	const FActorSpawnParameters SpawnParameters;
	const FVector Location = ProjectSpawner->GetComponentLocation();
	const FRotator Rotation = ProjectSpawner->GetComponentRotation();
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileToSpawn, Location, Rotation, SpawnParameters);
}

