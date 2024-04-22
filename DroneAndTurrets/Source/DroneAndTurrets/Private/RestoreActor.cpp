// Fill out your copyright notice in the Description page of Project Settings.


#include "RestoreActor.h"

#include "HitBoxComp.h"

// Sets default values
ARestoreActor::ARestoreActor()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	RootComponent = MeshComponent;
}

void ARestoreActor::BeginPlay()
{
	Super::BeginPlay();
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ARestoreActor::OverlapBegin);
}

void ARestoreActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARestoreActor::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UHitBoxComp* HitBoxComp = Cast<UHitBoxComp>(OtherComp);
	if(HitBoxComp)
	{
		switch(RestoreType)
		{
		case ERestoreType::AmmoRestore:
			{
				HitBoxComp->RechargeAmmo(DataForRestore);
				break;
			}
		case ERestoreType::HealthRestore:
			{
				HitBoxComp->Healing(static_cast<float>(DataForRestore));
				break;
			}
		}
		this->Destroy();
	}
}

