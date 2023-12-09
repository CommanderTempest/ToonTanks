// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleCom = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule collider"));
	RootComponent = CapsuleCom;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("base mesh"));
	BaseMesh->SetupAttachment(CapsuleCom);
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("turret mesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("bullet"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	TurretMesh->SetWorldRotation(FMath::RInterpTo(
		TurretMesh->GetComponentRotation(), 
		LookAtRotation, 
		UGameplayStatics::GetWorldDeltaSeconds(this), 
		25.f
		));
	
}

void ABasePawn::Fire()
{
	FVector ProjectileSpawnPointLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator ProjectileSpawnPointRotation = ProjectileSpawnPoint->GetComponentRotation();

	// DrawDebugSphere(
	// 	GetWorld(),
	// 	ProjectileSpawnPointLocation,
	// 	25.f,
	// 	12,
	// 	FColor::Red,
	// 	false,
	// 	3.f
	// );
	GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPointLocation, ProjectileSpawnPointRotation);
}






