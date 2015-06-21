// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Curve.h"
#include "Classes/Particles/ParticleSystem.h"
#include "Guardian.h"

#include "Enemies.generated.h"


UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EnemyTypeEnum : uint8
{
	Aubergine 	UMETA(DisplayName = "Aubergine"),
	Mushroom 	UMETA(DisplayName = "Mushroom"),
	Chili	UMETA(DisplayName = "Chili")
};

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EnemyMoveTypeEnum : uint8
{
	Standard 	UMETA(DisplayName = "Standard"),
	Tank 	UMETA(DisplayName = "Tank"),
	Fast	UMETA(DisplayName = "Fast")
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
	EnemyTypeEnum enemyType;

	// Hitpoints of Enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyProps")
	int32 hitPoints;

	// whether the player can damage the enemy or will receive damage when attacking it - only used for chily by now
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyProps")
	bool isEnemyVulnerable; //default value is true

	// Score the player gets for killing this enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyProps")
	int32 baseScore;

	// overall Speed-Factor of Enemy that defines how fast he is moving - intended to be used for different difficulties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float speedFactor;

	// Speed-Factor that defines how fast he is jumping - intended to be used to set up general movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float baseSpeedJump;

	// Linear Interpolation between constant forward movement (0) and speed depending on how steep the spline is (1)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float jumpLerp;

	// Speed-Factor that defines how fast he is walking - intended to be used to set up general movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float baseSpeedWalk;

	// How fast the enemy rotates towards the new jumpdirection between jumps, while idling
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float rotationLerpSpeed;
	
	// Spline Component List - where the enemy will move along
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	TArray<ACurve*> curveList;

	//type of Enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	EnemyMoveTypeEnum enemyMoveType;

	// Spline Component List - where the enemy will walk along
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	TArray<bool> walkingList;

	// index of Current Spline the enemy is moving on
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	int32 currentSpline;
	
	// Distance Percentage the enemy is located on the current Spline
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	float distPerc;

	// Distance Percentage the enemy is located on the current Spline
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool isIdle;

	// Distance Percentage the enemy is located on the current Spline
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float idleTime;
	
	// Distance Percentage the enemy is located on the current Spline
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float idleCurrentTime;

	// Distance Percentage the enemy is located on the current Spline
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool isWalking;

	// the point where the knifes spawn (i.e. the toaster)
	UPROPERTY(BlueprintReadWrite, Category = "EnemyProps")
	FTransform knifeSpawn;

	// Which Guardian this Enemy will be reducing hitpoints when reaching the end of its path
	UPROPERTY(BlueprintReadWrite, Category = "EnemyProps")
	GuardianTypeEnum guardianHitCaseEnum;

	// Guardian Rice Reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyProps")
	AGuardian *guardianRice;

	// Guardian Toast Reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyProps")
	AGuardian *guardianToast;


	///
	///	UFUNCTIONS
	///

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// MoveEnemyAlongSpline
	UFUNCTION(BlueprintCallable, Category = "MovementFunctions")
	void MoveEnemyAlongSpline();

	// Rotate the enemy towards the jumpdirection
	UFUNCTION(BlueprintCallable, Category = "MovementFunctions")
		void Rotate(float deltaTime);

	// Calculate the new Distance Percentage for moving the Enemy along its current Spline
	UFUNCTION(BlueprintCallable, Category = "MovementFunctions")
	void CalculateDistancePercentage(float deltaTime);

	// Check whether an Enemy reached the End of this or all Splines
	UFUNCTION(BlueprintCallable, Category = "MovementFunctions")
	bool CheckDistancePercentage();

	// spawns the knife projectile that is shot towards this enemy
	UFUNCTION(BlueprintCallable, Category = "ReceiveDmgFunctions")
		void spawnKnife(GuardianTypeEnum guardianType);

	// execute the projectile shot
	UFUNCTION(BlueprintImplementableEvent, Category = "ReceiveDmgFunctions")
		void spawnKnifeExecute();

	// Take calculated Damage and assign it to enemy
	UFUNCTION(BlueprintCallable, Category = "ReceiveDmgFunctions")
		void GotHit(GuardianTypeEnum guardianType);

	// plays all the Effects(particles, sounds, giblets...) when an Enemy got hit by an projectile  - but has remaining hitpoints
	UFUNCTION(BlueprintImplementableEvent, Category = "ReceiveDmgFunctions")
		void GotHitFeedback();

	// plays all the Effects when an Enemy dies (particles, sounds, giblets...)
	UFUNCTION(BlueprintImplementableEvent, Category = "ReceiveDmgFunctions")
		void diedFeedback(); 

	// trigger event when guardian rice gets hit 
	UFUNCTION(BlueprintImplementableEvent, Category = "SendDmgFunctions")
		void hitRice();

	// trigger event when guardian toast gets hit 
	UFUNCTION(BlueprintImplementableEvent, Category = "SendDmgFunctions")
		void hitToast(); 


};
