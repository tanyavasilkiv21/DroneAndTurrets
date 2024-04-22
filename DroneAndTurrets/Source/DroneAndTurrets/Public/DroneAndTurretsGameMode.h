// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DroneAndTurretsGameMode.generated.h"

class ATurret;

UCLASS()
class DRONEANDTURRETS_API ADroneAndTurretsGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	ADroneAndTurretsGameMode();
	virtual void Tick(float DeltaSeconds) override;
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
private:
	UPROPERTY(EditDefaultsOnly)
	int32 TurretsOnLevel;
	int32 CounterOfTurrets();
public:
	void ActorDied(AActor* DeadActor);
	
};
