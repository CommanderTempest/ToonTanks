// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "TankPawn.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankPawn : public ABasePawn
{
	GENERATED_BODY()

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	public:
		ATankPawn();
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
		APlayerController* GetTankPlayerController() const {return TankPlayerController;}
	private:
		UPROPERTY(VisibleAnywhere, Category = "Components")
		class USpringArmComponent* Spring;

		UPROPERTY(VisibleAnywhere, Category = "Components")
		class UCameraComponent* Camera;

		UPROPERTY(EditAnywhere, Category = "Movement")
		float Speed = 300.f;

		UPROPERTY(EditAnywhere, Category = "Movement")
		float TurnRate = 120.f;

		void Move(float Value);
		void Turn(float Value);

		APlayerController* TankPlayerController;
};
