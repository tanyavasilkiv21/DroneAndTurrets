// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AmmoWidget.generated.h"

class ADrone;

UCLASS()
class DRONEANDTURRETS_API UAmmoWidget : public UUserWidget
{
private:
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	UFUNCTION(BlueprintPure)
	int32 GetCurrentAmmo() const;
	ADrone* Player;
};
