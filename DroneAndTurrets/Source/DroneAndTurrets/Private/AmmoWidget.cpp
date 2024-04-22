// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoWidget.h"

#include "Drone.h"
#include "Kismet/GameplayStatics.h"

void UAmmoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Player = Cast<ADrone>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

int32 UAmmoWidget::GetCurrentAmmo() const
{
	if(Player)
	{
		return Player->GetQuantityOfAmmo();
	}
	return 0;
}
