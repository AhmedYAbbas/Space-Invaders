// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerSpaceship.generated.h"

class AProjectile;
class UCameraComponent;
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
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* ProjectSpawner;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile> ProjectileToSpawn;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 1.0f;

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Shoot();
};
