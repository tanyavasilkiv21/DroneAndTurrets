// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"
#include "Projectile.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HealthComponent.h"
#include "HitBoxComp.h"
#include "InputActionValue.h"
#include "InterchangeResult.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ADrone::ADrone()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = true;
	StartPointForShoot = CreateDefaultSubobject<USceneComponent>(TEXT("StartPointForShoot"));
	StartPointForShoot->SetupAttachment(CameraComponent);
	HitBoxComp = CreateDefaultSubobject<UHitBoxComp>(TEXT("HitBox"));
	HitBoxComp->SetupAttachment(this->GetMesh());

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	
	CurrentQuantityOfAmmo = MaxQuantityOfAmmo;
}

void ADrone::BeginPlay()
{
	Super::BeginPlay();
	if(const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DroneContext, 0);
		}
	}
}

void ADrone::Move(const FInputActionValue& Value)
{
	const FVector3d MoveVector = Value.Get<FVector3d>();

	const FVector Forward = GetActorForwardVector();
	AddMovementInput(Forward * MoveVector.Y);
	const FVector Right = GetActorRightVector();
	AddMovementInput(Right * MoveVector.X);
	const FVector Up = GetActorUpVector();
	AddMovementInput(Up *  MoveVector.Z);
}

void ADrone::Look(const FInputActionValue& Value)
{
	const FVector2d LookVector = Value.Get<FVector2d>();
	AddControllerPitchInput(-1 * LookVector.Y);
	AddControllerYawInput(LookVector.X);
}

void ADrone::Shoot()
{
	if(!IsNotEnoughAmmo())
	{
		GetWorld()->SpawnActor<AProjectile>(ProjectileClass, StartPointForShoot->GetComponentLocation(), StartPointForShoot->GetComponentRotation());
		CurrentQuantityOfAmmo--;
	}
}

void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("hp: %f"), HealthComponent->GetHP());
}

// Called to bind functionality to input
void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
			&ADrone::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this,
			&ADrone::Look);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this,
			&ADrone::Shoot);
	}
	
}


bool ADrone::IsNotEnoughAmmo() const
{
	return (CurrentQuantityOfAmmo == 0);
}

int32 ADrone::GetQuantityOfAmmo() const
{
	return CurrentQuantityOfAmmo;
}

int32 ADrone::GetMaxQuantityOfAmmo() const
{
	return MaxQuantityOfAmmo;
}

void ADrone::SetQuantityOfAmmo(int32 DataOfQuantityOfAmmo)
{
	CurrentQuantityOfAmmo = DataOfQuantityOfAmmo;
}

