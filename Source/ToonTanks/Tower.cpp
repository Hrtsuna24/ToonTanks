// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (CheckIfTankInRange())
    {
        // rotate if is
        RotateTurret(Tank->GetActorLocation());
    }
    
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    // PlayerControlerRef = Cast<APlayerController>(GetController());
    GetWorldTimerManager().SetTimer(FireRateTimerHandel, this, &ATower::CheckFireCondition, FireRete, true);
}

void ATower::CheckFireCondition()
{
    if (CheckIfTankInRange() && Tank->bAlive && Tank != nullptr)
    {
        Fire();
    }
}

bool ATower::CheckIfTankInRange()
{
    if (Tank)
    {
        // Find distance to the Tank
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        if (Distance <= FireRange)  // check see tank in range
            return true;
    }
    return false;
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
    Destroy();
}