// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "SaveGameKitchenGuardians.generated.h"

/**
 * 
 */
UCLASS()
class KITCHENGUARDIANS_API USaveGameKitchenGuardians : public USaveGame
{
	GENERATED_BODY()
	
public:
	USaveGameKitchenGuardians(const FObjectInitializer& ObjectInitializer);

	///
	///	UPROPERTYS
	///

	// Name of Player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGameProps")
	FString playerName;

	// List of Saved Scores from Player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGameProps")
	TArray<int32> highScoreList;

	///
	///	UFUNCTIONS
	///

	// Add First Score and Name
	UFUNCTION(BlueprintCallable, Category = "SaveGameFunctions")
	void AddFirstScore(int32 firstScore, FString newPlayerName);

	// Save or Discard new Score
	UFUNCTION(BlueprintCallable, Category = "SaveGameFunctions")
	void SaveNewScore(int32 newScore);
	
};
