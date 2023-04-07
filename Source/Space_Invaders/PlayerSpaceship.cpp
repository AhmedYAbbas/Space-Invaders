// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpaceship.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
APlayerSpaceship::APlayerSpaceship()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerSpaceship::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
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
	}
	
}

void APlayerSpaceship::Move(const FInputActionValue& Value)
{
	const float DirectionValue = Value.Get<float>();
	AddMovementInput(GetActorRightVector(), DirectionValue);
}

