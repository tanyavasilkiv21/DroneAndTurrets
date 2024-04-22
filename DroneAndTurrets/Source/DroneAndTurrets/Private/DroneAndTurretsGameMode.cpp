// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneAndTurretsGameMode.h"

#include "Drone.h"
#include "Turret.h"
#include "Kismet/GameplayStatics.h"

void ADroneAndTurretsGameMode::BeginPlay()
{
	Super::BeginPlay();
	TurretsOnLevel = CounterOfTurrets();
}

void ADroneAndTurretsGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(TurretsOnLevel == 0)
	{
		GameOver(true);
	}
}

void ADroneAndTurretsGameMode::ActorDied(AActor* DeadActor)
{
	if(ADrone* Drone = Cast<ADrone>(DeadActor))
	{
		Drone->DisableInput(Cast<APlayerController>(Drone->GetController()));
		Drone->SetHidden(true);
		GameOver(false);
	}
	else if(ATurret* Turret = Cast<ATurret>(DeadActor))
	{
		Turret->Destroy();
		TurretsOnLevel--;
	}
}


int32 ADroneAndTurretsGameMode::CounterOfTurrets()
{
	TArray<AActor*> TurretsInTheWorld;
	UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), TurretsInTheWorld);
	return TurretsInTheWorld.Num();
}
