// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

ATankPawn::ATankPawn()
{
    Spring = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    Spring->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(Spring);
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    // binding inputs to functions
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATankPawn::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATankPawn::Turn);
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

