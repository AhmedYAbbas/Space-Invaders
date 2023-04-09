// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemySpaceship.generated.h"

class UCapsuleComponent;

UCLASS()
class SPACE_INVADERS_API AEnemySpaceship : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpaceship();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* CapsuleComponent;
	

	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector DeltaZLocation = FVector(0, 0, -100.0f);

	UPROPERTY(EditAnywhere)
	FVector LineTraceDistance = FVector(0, 0, -250.0f);
	
	inline int32 static MovingDirection = 1;
	inline float static DeltaY = 250.0f;
	
	UFUNCTION()
	void ChangeMovementDirection(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
