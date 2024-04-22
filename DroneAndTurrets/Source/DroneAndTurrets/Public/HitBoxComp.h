// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "HitBoxComp.generated.h"


class UHealthComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRONEANDTURRETS_API UHitBoxComp : public UBoxComponent
{
	GENERATED_BODY()

public:	
	UHitBoxComp();

protected:
	virtual void BeginPlay() override;
private:
	UHealthComponent* HealthComponent;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void RechargeAmmo(int32 NewAmmo);
	void Healing(float HealHP);
	void Damaging(float Damage);
		
};
