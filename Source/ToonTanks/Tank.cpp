// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
//#include "Engine/World.h"

ATank::ATank()
{

    SpringArmCom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArmCom->SetupAttachment(RootComponent);

    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComp->SetupAttachment(SpringArmCom);

    bAlive = true;
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive = false;
    //Destroy();
}

void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

    PlayerInputComponent->BindAction(
        TEXT("Fire"),
        IE_Released,
        this,
        &ATank::Fire);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (PlayerControlerRef)
    {
        FHitResult HitRes;
        PlayerControlerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,
                                                    false,
                                                    HitRes);
        // HitRes.Impact;
        // DrawDebugSphere(
        //     GetWorld(),
        //     HitRes.ImpactPoint,
        //     25,
        //     12,
        //     FColor::Red,
        //     false,
        //     -1);
        RotateTurret(HitRes.ImpactPoint);
    }
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
    Super::BeginPlay();

    PlayerControlerRef = Cast<APlayerController>(GetController());
}

void ATank::Move(float Value)
{
    // UE_LOG(LogTemp, Display, TEXT("Your message %f"), Value);
    FVector DeltaLoc(0.f);
    // X = Value * Deltatime * Speed
    DeltaLoc.X = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * TankSpeed;
    DeltaLoc.X += Value;
    AddActorLocalOffset(DeltaLoc, true);
}

void ATank::Turn(float Value)
{
    FRotator DeltaRot = FRotator::ZeroRotator;
    DeltaRot.Yaw = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate;
    AddActorLocalRotation(DeltaRot, true);
}
