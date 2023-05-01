// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//#include "Components/CapsuleComponent.h"
#include "BasePawn.generated.h"

class USoundBase;



UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();
	// VisibleAnywhere
	// EditAnywhere
	// VisibleInstanceOnly - тільки в елементах в грі
	// VisibleDefaultsOnly - в бп
	// EditDefaultsOnly - в бп
	// EditInstaEditDefaultsOnlynceOnly - в бп
	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite) - можна ставити в бп в граф
	// UPROPERTY(EditAnywhere, BlueprintReadOnly) - в графі тіки читаємо
	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAcces = "true")) - довзоляє юзати дані з приватної секції

	// категорії в бп можна створити через 
	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Назва категорії",meta = (AllowPrivateAcces = "true"))
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent *CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent*  BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent*  TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent *ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShake;

protected:

	void RotateTurret(FVector LookAtTarget);

	void Fire();
};
