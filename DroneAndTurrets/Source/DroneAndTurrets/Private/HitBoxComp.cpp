// Fill out your copyright notice in the Description page of Project Settings.


#include "HitBoxComp.h"

#include "Drone.h"
#include "HealthComponent.h"

UHitBoxComp::UHitBoxComp()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHitBoxComp::BeginPlay()
{
	Super::BeginPlay();
	auto HealthRef = GetOwner()->GetComponentByClass(UHealthComponent::StaticClass());
	if(HealthRef)
	{
		HealthComponent = Cast<UHealthComponent>(HealthRef);
	}
}

void UHitBoxComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHitBoxComp::RechargeAmmo(int32 NewAmmo)
{
	if(ADrone* Drone = Cast<ADrone>(this->GetOwner()))
	{
		if(Drone->GetMaxQuantityOfAmmo() == Drone->GetQuantityOfAmmo())
		{
			return;
		}
		if(Drone->GetQuantityOfAmmo() == 0)
		{
			Drone->SetQuantityOfAmmo(NewAmmo);
		}
		if(Drone->GetQuantityOfAmmo() + NewAmmo > Drone->GetMaxQuantityOfAmmo())
		{
			Drone->SetQuantityOfAmmo(Drone->GetMaxQuantityOfAmmo());
		}
		if(Drone->GetQuantityOfAmmo() + NewAmmo < Drone->GetMaxQuantityOfAmmo())
		{
			Drone->SetQuantityOfAmmo(Drone->GetQuantityOfAmmo()+NewAmmo);
		}
		
	}
}

void UHitBoxComp::Healing(float HealHP)
{
	HealthComponent->HealDamage(HealHP);
}

void UHitBoxComp::Damaging(float Damage)
{
	HealthComponent->ApplyDamage(Damage);
}

