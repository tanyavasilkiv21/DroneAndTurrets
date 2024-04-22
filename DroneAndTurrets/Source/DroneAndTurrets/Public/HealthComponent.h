// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


class ADroneAndTurretsGameMode;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRONEANDTURRETS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	float MaxHP = 100.f;
	UPROPERTY(VisibleAnywhere)
	float CurrentHP;

	ADroneAndTurretsGameMode* DroneAndTurretsGameMode;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool IsDead() const;
	void ApplyDamage(float DataDamage);
	void HealDamage(float DataHeal);
	float GetHP();
};
