// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "SaveGameKitchenGuardian.generated.h"

/**
 * 
 */
UCLASS()
class KITCHENGUARDIANS_API USaveGameKitchenGuardian : public USaveGame
{
	GENERATED_BODY()
	
public:
	USaveGameKitchenGuardian(const FObjectInitializer& ObjectInitializer);

	///
	///	UPROPERTYS
	///

	// List of Player names
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGameProps")
	TArray<FString> playerNameList;

	// List of Saved Scores from Player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGameProps")
	TArray<int32> highScoreList;

	// Bool for Restart logic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGameProps")
	bool wasRestart;

	///
	///	UFUNCTIONS
	///

	// Add First Score and Name
	UFUNCTION(BlueprintCallable, Category = "SaveGameFunctions")
	void AddFirstScore(int32 firstScore);

	// Save or Discard new Score
	UFUNCTION(BlueprintCallable, Category = "SaveGameFunctions")
	int32 SaveNewScoreAndReturnIndex(int32 newScore);

	// Change Name inside List
	UFUNCTION(BlueprintCallable, Category = "SaveGameFunctions")
	void ChangePlayerName(int32 listIndex, FString newPlayerName);
	
};
