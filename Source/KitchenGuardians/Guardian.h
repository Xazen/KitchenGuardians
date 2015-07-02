// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Guardian.generated.h"



UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class GuardianTypeEnum : uint8
{
	Toaster 	UMETA(DisplayName = "Toaster"),
	Rice 	UMETA(DisplayName = "Rice")
};

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class AttackTypeEnum : uint8
{
	Tap 	UMETA(DisplayName = "Tap"),
	Swipe 	UMETA(DisplayName = "Swipe")
};

UCLASS()
class KITCHENGUARDIANS_API AGuardian : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AGuardian();
	
	
	///
	///	UPROPERTYS
	///


	//type of Guardian
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GuardianPropsBalancing")
		GuardianTypeEnum guardianType;
	
	// hitpoints of this Guardian
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GuardianPropsBalancing")
		int32 hitpoints;


	// initial and maximum amount of projectiles of this Guardian
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AmmunitionBalancing")
		float projectilesMaximum; //float because of possible "over time" or "swipe length" depletion

	// current amount of projectiles of this Guardian
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammunition")
		float projectilesCurrent; //float because of possible "over time" or "swipe length" depletion

	// whether this Guardian is currently in a reload process
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammunition")
		bool isReloading;

	// time in seconds the reload process takes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AmmunitionBalancing")
		float reloadTime;

	// time the Current Reload process has past
	UPROPERTY(BlueprintReadWrite, Category = "Ammunition")
		float reloadTimeCurrent;

	// temporarily stores the maximum amount of projectiles - because the maximum projectiles are used to display reload progress
	UPROPERTY(BlueprintReadWrite, Category = "Ammunition")
		float reloadTmpAmmoStore;


	// Flag to check whether the player failed to revive
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Feedback")
		bool isDead;
	
	// bool used to execute a red screen flash
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Feedback")
		bool doFlash;

	///
	///	UFUNCTIONS
	///

	// Calculates new Hitpoints after Guardian is hit by enemy - if necessary will initialize Revive Mechanic
	UFUNCTION(BlueprintCallable, Category = "HitpointsFunctions")
		void GotHit(); // i am not sure whether the enemyType matters
	
	// trigger event for shotFeedback
	UFUNCTION(BlueprintImplementableEvent, Category = "FeedbackFunctions")
		void ShotFeedback(); 

	// trigger event for gotHitFeedback
	UFUNCTION(BlueprintImplementableEvent, Category = "FeedbackFunctions")
		void GotHitFeedback(); 

	
	// Reduces the Ammunition by one - may not be applicable to Rice Guardian
	UFUNCTION(BlueprintCallable, Category = "AmmunitionFunctions")
		void Shot(int32 ammoCost);

		// Whether this guardian can shoot or not (depending on ammunition and hitpoints and active-status)
	UFUNCTION(BlueprintCallable, Category = "AmmunitionFunctions")
		bool canShoot();

	// this function executes manual reload, auto reload when empty and handles the time the reload takes
	UFUNCTION(BlueprintCallable, Category = "AmmunitionFunctions")
		void reloadAmmo(float deltaSeconds);

	// this function executes manual reload, auto reload when empty and handles the time the reload takes
	UFUNCTION(BlueprintCallable, Category = "AmmunitionFunctions")
		void initReload();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
};
