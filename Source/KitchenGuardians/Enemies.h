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
	Mushroom 	UMETA(DisplayName = "Mushroom"),
	Chili		UMETA(DisplayName = "Chili"),
	Pumpkin		UMETA(DisplayName = "Pumpkin"),
	PumpkinBlue UMETA(DisplayName = "PumpkinBlue"),
	NoType		UMETA(DisplayName = "NoType")
};

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EnemyMoveTypeEnum : uint8
{
	Standard 	UMETA(DisplayName = "Standard"),
	Tank 		UMETA(DisplayName = "Tank"),
	Fast		UMETA(DisplayName = "Fast")
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyPropsBalancing")
	EnemyTypeEnum enemyType;

	// Hitpoints of Enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyPropsBalancing")
	int32 hitPoints;

	// How much Damage the Enemy receives via Tap
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyPropsBalancing")
		int32 dmgTap;
	// How much Damage the Enemy receives via Tap
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyPropsBalancing")
		int32 dmgSwipe;

	// Vector to determine Radial Force Position for Giblet Impulse when hit via Toast
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyProps")
		FVector RadialForcePosition;

	// whether the player can damage the enemy or will receive damage when attacking it - only used for chily by now
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyProps")
	bool isEnemyVulnerable; //default value is true

	// Score the player gets for killing this enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyPropsBalancing")
	int32 baseScore;

	// overall Speed-Factor of Enemy that defines how fast he is moving - intended to be used for different difficulties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementBalancing")
	float speedFactor;

	// Speed-Factor that defines how fast he is jumping - intended to be used to set up general movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementBalancing")
	float baseSpeedJump;

	// Linear Interpolation between constant forward movement (0) and speed depending on how steep the spline is (1)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementBalancing")
	float jumpLerp;

	// Speed-Factor that defines how fast he is walking - intended to be used to set up general movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementBalancing")
	float baseSpeedWalk;

	// How fast the enemy rotates towards the new jumpdirection between jumps, while idling
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementBalancing")
	float rotationLerpSpeed;
	
	// Spline Component List - where the enemy will move along
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	TArray<ACurve*> curveList;

	//type of Enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	EnemyMoveTypeEnum enemyMoveType;

	// Bool List, that shows which of the Splines the enemy will be walking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	TArray<bool> walkingList;

	// Float List, to define different Idle Times between jumps
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		TArray<float> idleList;

	// index of Current Spline the enemy is moving on
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	int32 currentSpline;
	
	// Distance Percentage the enemy is located on the current Spline
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	float distPerc;

	// Whether this enemy currently idles
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool isIdle;

	// How long this enemy will idle between jumps
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float idleTime;
	
	// How long this enemy currently idles
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float idleCurrentTime;

	// Whether this enemy currently walks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool isWalking;

	// the point where the knifes spawn (i.e. the toaster)
	UPROPERTY(BlueprintReadWrite, Category = "EnemyProps")
	FTransform knifeSpawn;

	// Which Guardian this Enemy will be reducing hitpoints when reaching the end of its path - unused
	UPROPERTY(BlueprintReadWrite, Category = "EnemyProps")
	GuardianTypeEnum guardianHitCaseEnum;

	// Guardian Toast Reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyProps")
	AGuardian *guardianToast;


	// The minimum Gibblet Impulse
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FeedbackPropsBalancing")
		int32 minGibbletImpulse;

	// The maximum Gibblet Impulse
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FeedbackPropsBalancing")
		int32 maxGibbletImpulse;

	// When to trigger the slowMo - (in percentages of the last Spline)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FeedbackPropsBalancing")
		float triggerSlowMoPercentage;

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


	// Take calculated Damage and assign it to enemy
	UFUNCTION(BlueprintCallable, Category = "ReceiveDmgFunctions")
		void GotHit(AttackTypeEnum attackType, FVector HitLocation);

	// plays all the Effects(particles, sounds, giblets...) when an Enemy got hit by a toast projectile  - but has remaining hitpoints
	UFUNCTION(BlueprintImplementableEvent, Category = "ReceiveDmgFunctions")
		void GotHitToastFeedback();

	// plays all the Effects(particles, sounds, giblets...) when an Enemy got hit by a swipe  - but has remaining hitpoints
	UFUNCTION(BlueprintImplementableEvent, Category = "ReceiveDmgFunctions")
		void GotHitRiceFeedback();

	// plays all the Effects when an Enemy dies via toast (particles, sounds, giblets...)
	UFUNCTION(BlueprintImplementableEvent, Category = "ReceiveDmgFunctions")
		void diedToastFeedback();

	// plays all the Effects when an Enemy dies via swipe (particles, sounds, giblets...)
	UFUNCTION(BlueprintImplementableEvent, Category = "ReceiveDmgFunctions")
		void diedRiceFeedback();

	// trigger event when Enemy Triggers Slowmo
	UFUNCTION(BlueprintImplementableEvent, Category = "SendDmgFunctions")
		void triggerSlowMoFeedback();

	// trigger event when guardian toast gets hit 
	UFUNCTION(BlueprintImplementableEvent, Category = "SendDmgFunctions")
		void hitToastFeedback(); 

	// trigger event when Bonus Enemy reaches End of Path 
	UFUNCTION(BlueprintImplementableEvent, Category = "MovementFunctions")
		void ReachedEndAsBonusEnemy();

	// Add Random Impulse to Gibblet
	UFUNCTION(BlueprintCallable, Category = "FeedbackFunctions")
		void AddGibbletImpulse2(UPrimitiveComponent* Gibblet);

	// trigger event when enemy blocks an attack (i.e. when he got attacked while being invulnerable)
	UFUNCTION(BlueprintImplementableEvent, Category = "SendDmgFunctions")
		void gotHitInvulnerableFeedback();


	// calculates the transparency of the shadow according to the distance to the ground
	UFUNCTION(BlueprintCallable, Category = "FeedbackFunctions")
		float calcDropShadowAlpha(float zDistance);
};
