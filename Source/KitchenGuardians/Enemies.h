// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Classes/Components/SplineComponent.h"
#include "Classes/Particles/ParticleSystem.h"

#include "Enemies.generated.h"

UCLASS()
class KITCHENGUARDIANS_API AEnemies : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties - Constructor
	AEnemies();

	///
	///	UPROPERTYS
	///

	// Hitpoints of Enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyProps")
	int8 hitPoints;

	// Damage of Enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyProps")
	uint8 baseDamage;

	// Score of Enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyProps")
	uint8 baseScore;

	// Speed of Enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyProps")
	float jumpSpeed;

	// Spline Component List
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyProps")
	TArray<USplineComponent*> splineList;

	// Current Spline
	UPROPERTY(BlueprintReadWrite, Category = "EnemyProps")
	uint8 currentSpline;
	
	// Distance Percentage
	UPROPERTY(BlueprintReadWrite, Category = "EnemyProps")
	float distPerc;

	// Micha will write something here
	UPROPERTY(BlueprintReadWrite, Category = "EnemyProps")
	uint8 botHitCase;

	// Guardian 1 Reference
	UPROPERTY(BlueprintReadWrite, Category = "EnemyProps")
	AActor *guardianOne;

	// Guardian 2 Reference
	UPROPERTY(BlueprintReadWrite, Category = "EnemyProps")
	AActor *guardianTwo;

	// Guardian 3 Reference
	UPROPERTY(BlueprintReadWrite, Category = "EnemyProps")
	AActor *guardianThree;

	///
	///	UFUNCTIONS
	///

	// MoveEnemyAlongSpline
	UFUNCTION(BlueprintCallable, Category = "EnemyFunctions")
	void MoveEnemyAlongSpline();

	// Micha will write something here
	UFUNCTION(BlueprintCallable, Category = "EnemyFunctions")
	void CalculateDistancePercentage(float deltaTime);

	// Micha will write something here
	UFUNCTION(BlueprintCallable, Category = "EnemyFunctions")
	void CheckDistancePercentage();

	// Take calculated Damage and assign it to enemy
	UFUNCTION(BlueprintCallable, Category = "EnemyFunctions")
	void GotHit(UParticleSystem *emitterTemplate, uint8 calculatedDamage);


};
