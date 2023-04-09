// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCluster.generated.h"

class UCapsuleComponent;

UCLASS()
class SPACE_INVADERS_API AEnemyCluster : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	AEnemyCluster();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	UCapsuleComponent* CapsuleComponent;
	
	UPROPERTY(EditAnywhere)
	int32 MovingDirection = 1;

	UPROPERTY(EditAnywhere)
	float DeltaY = 500.0f;

	UPROPERTY(EditAnywhere)
	float DeltaZ = -100.0f;

	UFUNCTION()
	void ChangeMovementDirection(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
