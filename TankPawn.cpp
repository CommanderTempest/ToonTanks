// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "DrawDebugHelpers.h"

ATankPawn::ATankPawn()
{
    Spring = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    Spring->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(Spring);
}

void ATankPawn::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	
    TankPlayerController = Cast<APlayerController>(GetController());
}

// Called every frame (extra for init)
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (TankPlayerController)
    {
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
        // DrawDebugSphere(
        //     GetWorld(),
        //     HitResult.ImpactPoint, 
        //     25.f,
        //     12,
        //     FColor::Red,
        //     false,
        //     -1.f
        // );
        RotateTurret(HitResult.ImpactPoint);
    }
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    // binding inputs to functions
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATankPawn::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATankPawn::Turn);

    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATankPawn::Fire);
}

void ATankPawn::Move(float Value) {
    //UE_LOG(LogTemp, Display, TEXT("Value: %f", Value));
    FVector DeltaLocation = FVector::ZeroVector;
    // X = Value * DeltaTime * Speed
	DeltaLocation.X = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed;

	AddActorLocalOffset(DeltaLocation, true);
}

void ATankPawn::Turn(float Value) {
    FRotator DeltaRotation = FRotator::ZeroRotator;
    DeltaRotation.Yaw = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate;

    AddActorLocalRotation(DeltaRotation, true);
}

