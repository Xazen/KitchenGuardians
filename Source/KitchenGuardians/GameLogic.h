// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Enemies.h" //in order to use the enum for its type
#include "Guardian.h" //in order to use the enum for its type

#include "GameLogic.generated.h"

UCLASS()
class KITCHENGUARDIANS_API AGameLogic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameLogic();

	///
	///	UPROPERTYS
	///

	// HighScore of Current Game Session
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSessionProps")
		int32 highScore;

	// whether the gamesession is over - may be removed and reworked with elegant do once stuffs
	UPROPERTY(BlueprintReadWrite, Category = "GameSessionProps")
		bool isGameover;
	
	// Kill Counter for Chillis
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSessionProps")
		int32 killCounterChillis;

	// Kill Counter for Mushrooms
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSessionProps")
		int32 killCounterMushrooms;

	// Kill Counter for Onions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSessionProps")
		int32 killCounterOnions;
	
	// The initial TimeDelta between Spawns
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawningEnemies")
		float spawnTimeDelta;


	///
	///	UFUNCTIONS
	///

	// Add a Score Value to the Current HighScore
	UFUNCTION(BlueprintCallable, Category = "ScoringFunctions")
		void AddScore(int32 addedScore, EnemyTypeEnum enemyType);

	// calculate a Score depending on the Enemy - the Type of Attack - a Multiplier and a Bonus (last are just predicted optional values with default values) - not used by now
	UFUNCTION(BlueprintCallable, Category = "ScoringFunctions")
		int32 calculateScore(EnemyTypeEnum enemyType, GuardianTypeEnum guardianType, int32 multiplier = 1, int32 bonus = 0);

	// Calculate the new spawnTimeDelta
	UFUNCTION(BlueprintCallable, Category = "SpawningFunctions")
		float newSpawnDeltaTime();


	// initializes the game over sequence
	UFUNCTION(BlueprintCallable, Category = "GameOver")
		void gameOver();

	// executes the game over sequence
	UFUNCTION(BlueprintImplementableEvent, Category = "GameOver")
		void gameOverExecute(); // i am not sure whether the enemyType matters

	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
	
};
