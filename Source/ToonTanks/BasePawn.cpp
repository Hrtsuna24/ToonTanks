// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Camera/CameraShakeBase.h"

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	// TODO: Visual/sound eff

	// DeathParticles
	if (DeathParticles)
		UGameplayStatics::SpawnEmitterAtLocation(this,
												 DeathParticles,
												 GetActorLocation(),
												 GetActorRotation());

	if (DeathSound)
		UGameplayStatics::PlaySoundAtLocation(this,
											  DeathSound,
											  GetActorLocation());

	if (DeathCameraShake)
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShake);
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0, ToTarget.Rotation().Yaw, 0);
	// or
	// LookAtRotation.Pitch = 0;
	// LookAtRotation.Roll = 0;
	// FRotator(0, ToTarget.Rotation().Yaw, 0)
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			5));
}

void ABasePawn::Fire()
{
	FVector ProjectileSpawnPointLoc = ProjectileSpawnPoint->GetComponentLocation();
	// DrawDebugSphere(
	// 	GetWorld(),
	// 	ProjectileSpawnPointLoc,
	// 	25,
	// 	12,
	// 	FColor::Blue,
	// 	false,
	// 	3
	// );
	// Spawn the projectile
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileClass,
		ProjectileSpawnPointLoc,
		ProjectileSpawnPoint->GetComponentRotation());

	Projectile->SetOwner(this);
}