// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "DroneAndTurretsGameMode.h"
#include "Kismet/GameplayStatics.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHP = MaxHP;
	DroneAndTurretsGameMode = Cast<ADroneAndTurretsGameMode>(UGameplayStatics::GetGameMode(this));
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UHealthComponent::IsDead() const
{
	return CurrentHP == 0;
}

void UHealthComponent::ApplyDamage(float DataDamage)
{
	CurrentHP -= FMath::Min(DataDamage, CurrentHP);
	if(IsDead() && DroneAndTurretsGameMode)
	{
		DroneAndTurretsGameMode->ActorDied(this->GetOwner());
	}
	
}

void UHealthComponent::HealDamage(float DataHeal)
{
	if(CurrentHP == MaxHP)
	{
		return;
	}
	if(CurrentHP + DataHeal < MaxHP)
	{
		CurrentHP += DataHeal;
	}
	if(CurrentHP + DataHeal > MaxHP)
	{
		CurrentHP += (MaxHP - CurrentHP);
	}
}

float UHealthComponent::GetHP()
{
	return CurrentHP;
}

