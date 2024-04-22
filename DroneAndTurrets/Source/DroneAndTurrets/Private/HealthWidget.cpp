// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthWidget.h"

#include "Drone.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"

void UHealthWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Player = Cast<ADrone>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

float UHealthWidget::CalculateHealthPercentage()
{
	if(Player)
	{
		PlayerHealthComponent = Cast<UHealthComponent>(Player->GetComponentByClass(UHealthComponent::StaticClass()));
		if(PlayerHealthComponent)
		{
			return PlayerHealthComponent->GetHP() / PlayerHealthComponent->GetMaxHP();
		}
	}
	return 0.f;
}
