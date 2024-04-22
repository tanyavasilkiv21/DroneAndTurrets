// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class DRONEANDTURRETS_API UHealthWidget : public UUserWidget
{
private:
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintPure)
	float CalculateHealthPercentage();

	UPROPERTY(VisibleAnywhere)
	AActor* Player;

	class UHealthComponent* PlayerHealthComponent;
};
