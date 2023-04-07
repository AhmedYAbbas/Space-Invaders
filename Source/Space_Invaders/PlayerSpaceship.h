// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerSpaceship.generated.h"

class UInputMappingContext;
struct FInputActionValue;
class UInputAction;

UCLASS()
class SPACE_INVADERS_API APlayerSpaceship : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerSpaceship();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 0.0f;

	void Move(const FInputActionValue& Value);
};
