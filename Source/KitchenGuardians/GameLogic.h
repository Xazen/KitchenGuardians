// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
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
	UPROPERTY(BlueprintReadWrite, Category = "GameSessionProps")
		uint32 highScore;

	// The initial TimeDelta between Spawns
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawningEnemies")
		float spawnTimeDelta;


	///
	///	UFUNCTIONS
	///

	// Add a Score Value to the Current HighScore
	UFUNCTION(BlueprintCallable, Category = "ScoringFunctions")
		void AddScore(uint32 addedScore);

	// calculate a Score depending on the Enemy - the Type of Attack - a Multiplier and a Bonus (last are just predicted optional values with default values)
	//default values just working with int32 sorry :(
	UFUNCTION(BlueprintCallable, Category = "ScoringFunctions")
		uint32 calculateScore(uint8 enemyType, uint8 attackType, int32 multiplier = 1, int32 bonus = 0);

	// Calculate the new spawnTimeDelta
	UFUNCTION(BlueprintCallable, Category = "SpawningFunctions")
		float newSpawnDeltaTime();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
