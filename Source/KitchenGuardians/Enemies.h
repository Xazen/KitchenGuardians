// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Classes/Components/SplineComponent.h"
#include "Classes/Particles/ParticleSystem.h"

#include "Enemies.generated.h"


UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class enemyTypeEnum : uint8
{
	VE_Meat 	UMETA(DisplayName = "Meat"),
	VE_Vegetable 	UMETA(DisplayName = "Vegetable"),
	VE_Drink	UMETA(DisplayName = "Drink")
};


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

	//type of Enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyProps")
		enemyTypeEnum enemyType;


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

	// index of Current Spline
	UPROPERTY(BlueprintReadWrite, Category = "EnemyProps")
	uint8 currentSpline;
	
	// Distance Percentage the enemy is located on the current Spline
	UPROPERTY(BlueprintReadWrite, Category = "EnemyProps")
	float distPerc;

	// Which Guardian this Enemy will be reducing hitpoints when reaching the end of its path
	UPROPERTY(BlueprintReadWrite, Category = "EnemyProps")
	uint8 guardianHitCase;

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

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// MoveEnemyAlongSpline
	UFUNCTION(BlueprintCallable, Category = "EnemyFunctions")
	void MoveEnemyAlongSpline();

	// Calculate the new Distance Percentage for moving the Enemy along its current Spline
	UFUNCTION(BlueprintCallable, Category = "EnemyFunctions")
	void CalculateDistancePercentage(float deltaTime);

	// Check whether an Enemy reached the End of this or all Splines
	UFUNCTION(BlueprintCallable, Category = "EnemyFunctions")
	void CheckDistancePercentage();

	// Take calculated Damage and assign it to enemy
	UFUNCTION(BlueprintCallable, Category = "EnemyFunctions")
	void GotHit(uint8 calculatedDamage);

	// plays all the Effects(particles, sounds, giblets...) when an Enemy got hit by an projectile  - but has remaining hitpoints
	UFUNCTION(BlueprintCallable, Category = "EnemyFunctions")
	void GotHitEffect(UParticleSystem *emitterTemplate);

	// plays all the Effects when an Enemy dies (particles, sounds, giblets...)
	UFUNCTION(BlueprintCallable, Category = "EnemyFunctions")
	void DiedEffect(UParticleSystem *emitterTemplate);


};
