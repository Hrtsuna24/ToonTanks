// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TTGameMode.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API ATTGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor *DeadActor);

private:
 	class ATank* Tank;
	class ATTPlayerController* PlayerController;

	float StartDelay = 3.f;
	void HandleGameStart();
	
	int32 TowerAmount = 0;
	int32 GetTowerCount();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);
};
