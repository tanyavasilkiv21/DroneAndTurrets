// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "Drone.h"
#include "HealthComponent.h"
#include "HitBoxComp.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurretBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = TurretBaseMesh;
	TurretPushkaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PushkaMesh"));
	TurretPushkaMesh->SetupAttachment(RootComponent);
	StartPointForShoot = CreateDefaultSubobject<USceneComponent>(TEXT("StartPointForShoot"));
	StartPointForShoot->SetupAttachment(TurretPushkaMesh);
	HitBoxComp = CreateDefaultSubobject<UHitBoxComp>(TEXT("HitBoxComp"));
	HitBoxComp->SetupAttachment(TurretPushkaMesh);
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Comp"));
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<ADrone>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimeHandle, this, &ATurret::Shoot, FireRate, true);
}

bool ATurret::InFireRange()
{
	if(Player)
	{
		float Distance = FVector::Dist(this->GetActorLocation(), Player->GetActorLocation());
		if(Distance <= FireRange)
		{
			FVector Start = StartPointForShoot->GetComponentLocation();
			FVector End = Player->GetActorLocation() ;
			FHitResult HitResult;
			FCollisionQueryParams CollisionParams;
			CollisionParams.AddIgnoredActor(this);
			
			//DrawDebugLine(GetWorld(), Start, End, FColor::Black, true);
			
			if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
			{
				//UE_LOG(LogTemp, Warning, TEXT("Actor name: %s"), *HitResult.GetActor()->GetName());
				//DrawDebugLine(GetWorld(), Start, End, FColor::Magenta, true);
				if(HitResult.GetActor() == Player)
				{
					return true;
				}
			}		
		}
	}
	return false;
}

void ATurret::RotatePawn(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretPushkaMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(ToTarget.Rotation().Pitch, ToTarget.Rotation().Yaw, 0.f);
	TurretPushkaMesh->SetWorldRotation(FMath::RInterpTo(TurretPushkaMesh->GetComponentRotation(), LookAtRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this), 40.f)
		);
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(InFireRange())
	{
		RotatePawn(Player->GetActorLocation());
	}
}

void ATurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATurret::Shoot()
{
	if(InFireRange() && !(Player->IsHidden()))
	{
		GetWorld()->SpawnActor<AProjectile>(ProjectileClass, StartPointForShoot->GetComponentLocation(), StartPointForShoot->GetComponentRotation());
	}
}

