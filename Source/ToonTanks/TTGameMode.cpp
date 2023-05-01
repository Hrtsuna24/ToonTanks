// Fill out your copyright notice in the Description page of Project Settings.

#include "TTGameMode.h"
#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "TTPlayerController.h"

void ATTGameMode::ActorDied(AActor *DeadActor)
{
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if (Tank->getAPlayerController())
        {
            PlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);
    }
    else if (ATower *DestroedTower = Cast<ATower>(DeadActor))
    {
        DestroedTower->HandleDestruction();
        --TowerAmount;
        if(TowerAmount == 0)
        {
            GameOver(true);
        }
    }
}

void ATTGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();
}

void ATTGameMode::HandleGameStart()
{
    TowerAmount = GetTowerCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    PlayerController = Cast<ATTPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();
    if (PlayerController)
    {
        PlayerController->SetPlayerEnabledState(false);
        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate InputDelegate = FTimerDelegate::CreateUObject(
            PlayerController,
            &ATTPlayerController::SetPlayerEnabledState,
            true);
        GetWorldTimerManager().SetTimer(
            PlayerEnableTimerHandle,
            InputDelegate,
            StartDelay,
            false);
    }
}


int32 ATTGameMode::GetTowerCount()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    return Towers.Num();
}