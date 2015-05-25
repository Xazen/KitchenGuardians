// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Guardian.generated.h"



UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class guardianTypeEnum : uint8
{
	VE_Toaster 	UMETA(DisplayName = "Toaster"),
	VE_Rice 	UMETA(DisplayName = "Rice"),
	VE_Ice	UMETA(DisplayName = "Ice")
};



UCLASS()
class KITCHENGUARDIANS_API AGuardian : public AActor
{
	GENERATED_BODY()
	
public:	

	///
	///	UPROPERTYS
	///


	//type of Guardian
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GuardianProps")
		guardianTypeEnum guardianType;
	

	// wether this Guardian is currently active or not - need to figure something out for always on or select guardian mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GuardianProps")
		bool activated;

	// hitpoints of this Guardian
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GuardianProps")
		uint8 hitpoints;


	// initial and maximum amount of projectiles of this Guardian
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammunition")
		float projectilesMaximum; //float because of possible "over time" or "swipe length" depletion

	// current amount of projectiles of this Guardian
	UPROPERTY(BlueprintReadWrite, Category = "Ammunition")
		float projectilesCurrent; //float because of possible "over time" or "swipe length" depletion


	// time in seconds it takes to gain one projectile
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammunition")
		float projectilesRefillTime; //float because of possible "over time" or "swipe length" depletion

	// amount of maximum Taps necessary to Revive the Guardian, i.e. the target value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive Mechanic")
		uint8 reviveTapsMaximum;

	// amount of initial Taps Revive Process begins with
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive Mechanic")
		uint8 reviveTapsStart;

	// amount of current Taps of this Revive Process
	UPROPERTY(BlueprintReadWrite, Category = "Revive Mechanic")
		uint8 reviveTapsCurrent;

	// amount of Taps removed per second
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive Mechanic")
		uint8 reviveTapsRemovedSecond;

	// amount of Taps removed when hit via Enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive Mechanic")
		uint8 reviveTapsRemovedEnemy;

	// Hitpoints the Guardian gets after the first Revive
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive Mechanic")
		uint8 reviveHitpointsFirst;

	// Hitpoints the Guardian gets every additional Revive
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive Mechanic")
		uint8 reviveHitpointsNext;

	// Additional Taps necessary for the next revive (added on Top of reviveTapsMaximum after each revive)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive Mechanic")
		uint8 reviveTapsAdditional;

	// Flag to check whether the current revive is the first one
	UPROPERTY(BlueprintReadWrite, Category = "Revive Mechanic")
		bool reviveIsFirst;

	///
	///	UFUNCTIONS
	///

	// activates this guardian so that attacks can be performed with it
	UFUNCTION(BlueprintCallable, Category = "UsabilityFunctions")
		void Activate(); // i am not sure whether the enemyType matters

	// deactivates this guardian so that no attacks can be performed with it
	UFUNCTION(BlueprintCallable, Category = "UsabilityFunctions")
		void Deactivate(); // i am not sure whether the enemyType matters

	// Calculates new Hitpoints after Guardian is hit by enemy - if necessary will initialize Revive Mechanic
	UFUNCTION(BlueprintCallable, Category = "HitpointsFunctions")
		void GotHit(); // i am not sure whether the enemyType matters


	// Assigns new Values when after a successful revive
	UFUNCTION(BlueprintCallable, Category = "HitpointsFunctions")
		void Revive();

	// whether this Guardian has any hitpoints
	UFUNCTION(BlueprintCallable, Category = "HitpointsFunctions")
		bool isDead();
	
	// Reduces the Ammunition by one - may not be applicable to Rice Guardian
	UFUNCTION(BlueprintCallable, Category = "AmmunitionFunctions")
		void Shot();


	// Whether this guardian can shoot or not (depending on ammunition and hitpoints and active-status)
	UFUNCTION(BlueprintCallable, Category = "AmmunitionFunctions")
		bool canShoot();



	// Sets default values for this actor's properties
	AGuardian();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
