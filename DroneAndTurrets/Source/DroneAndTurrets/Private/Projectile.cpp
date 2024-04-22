// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "HitBoxComp.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	MovementComponent->InitialSpeed = 2000.f;
	MovementComponent->MaxSpeed = 2000.f;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OverlapBegin);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UHitBoxComp* HitBoxComp = Cast<UHitBoxComp>(OtherComp);
	if(HitBoxComp)
	{
		HitBoxComp->Damaging(Damage);
	}
	Destroy();
}

