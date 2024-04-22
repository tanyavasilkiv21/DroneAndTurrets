// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Turret.generated.h"

class AProjectile;
class ADrone;
class UHealthComponent;
class UHitBoxComp;

UCLASS()
class DRONEANDTURRETS_API ATurret : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditDefaultsOnly, Category = Components)
	UStaticMeshComponent* TurretBaseMesh;
	UPROPERTY(EditDefaultsOnly, Category = Components)
	UStaticMeshComponent* TurretPushkaMesh;
	UPROPERTY(EditDefaultsOnly, Category = Components)
	USceneComponent* StartPointForShoot;
	UPROPERTY(EditDefaultsOnly, Category = Components)
	UHitBoxComp* HitBoxComp;
	UPROPERTY(EditDefaultsOnly, Category = Components)
	UHealthComponent* HealthComponent;
	UPROPERTY(EditDefaultsOnly, Category = Components)
	UStaticMeshComponent* QuestionMarkMesh;
	UPROPERTY(EditDefaultsOnly, Category = Components)
	TSubclassOf<AProjectile> ProjectileClass;
	
	ADrone* Player;

	bool InFireRange();
	
	UPROPERTY(EditDefaultsOnly, Category = Fire)
	float FireRange = 1500.f;
	UPROPERTY(EditDefaultsOnly, Category = Fire)
	float FireRate = 2.f;
	
	FTimerHandle FireRateTimeHandle;
	
	void RotatePawn(FVector LookAtTarget);
	void Shoot();
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
