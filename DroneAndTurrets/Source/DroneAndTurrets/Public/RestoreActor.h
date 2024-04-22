 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RestoreActor.generated.h"

 UENUM(BlueprintType)
enum class ERestoreType
{
	NoType = 0,
	HealthRestore,
	AmmoRestore
};
UCLASS()
class DRONEANDTURRETS_API ARestoreActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ARestoreActor();
	
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditDefaultsOnly)
	ERestoreType RestoreType = ERestoreType::NoType;
	UPROPERTY(EditDefaultsOnly)
	int32 DataForRestore = 5;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
