// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemySpaceship.generated.h"

class UCapsuleComponent;
class AProjectile;

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

	UFUNCTION()
	bool CanShoot() const;

	UFUNCTION()
	void Shoot();

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* ProjectileSpawner;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile> ProjectileToSpawn;

	UPROPERTY(EditAnywhere)
	FVector LineTraceDistance = FVector(0, 0, -250.0f);

	inline TArray<AEnemySpaceship*> static ReadyEnemySpaceships;
	inline int32 static Index = 0;

	FTimerHandle ShootTimeHandle;

	UPROPERTY()
	bool bShoot = false;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
