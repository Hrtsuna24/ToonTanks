// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:

	ATank();

	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	
	APlayerController* getAPlayerController() const {return PlayerControlerRef;}

	bool bAlive;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArmCom;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* CameraComp;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float TankSpeed = 200;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 100;
	
	void Move(float Value);
	void Turn(float Value);

	UPROPERTY(EditAnywhere, Category = "Movement")
	APlayerController * PlayerControlerRef;
};
