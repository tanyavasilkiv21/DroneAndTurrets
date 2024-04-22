// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Drone.generated.h"

class UHealthComponent;
class UCameraComponent;
class USpringArmComponent;
class UHitBoxComp;
class AProjectile;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class DRONEANDTURRETS_API ADrone : public ACharacter
{
	GENERATED_BODY()

public:
	ADrone();

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* DroneContext;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* ShootAction;

	UPROPERTY(EditDefaultsOnly, Category = Components)
	USceneComponent* StartPointForShoot;
	UPROPERTY(EditDefaultsOnly, Category = Components)
	UHitBoxComp* HitBoxComp;
	UPROPERTY(EditDefaultsOnly, Category = Components)
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditDefaultsOnly, Category = Components)
	UCameraComponent* CameraComponent;
	UPROPERTY(EditDefaultsOnly, Category = Components)
	UHealthComponent* HealthComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = Projectiles)
	TSubclassOf<AProjectile> ProjectileClass;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Shoot();

	UPROPERTY(EditDefaultsOnly)
	int32 MaxQuantityOfAmmo = 20;
	UPROPERTY(EditDefaultsOnly)
	int32 CurrentQuantityOfAmmo;
	
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool IsNotEnoughAmmo() const;

	int32 GetQuantityOfAmmo() const;
	int32 GetMaxQuantityOfAmmo() const;
	void SetQuantityOfAmmo(int32 DataOfQuantityOfAmmo);
};
