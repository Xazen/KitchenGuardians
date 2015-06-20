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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GuardianProps")
		GuardianTypeEnum guardianType;
	

	// whether this Guardian is currently active or not - need to figure something out for always on or select guardian mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GuardianProps")
		bool activated;

	// hitpoints of this Guardian
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GuardianProps")
		int32 hitpoints;


	// initial and maximum amount of projectiles of this Guardian
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammunition")
		float projectilesMaximum; //float because of possible "over time" or "swipe length" depletion

	// current amount of projectiles of this Guardian
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammunition")
		float projectilesCurrent; //float because of possible "over time" or "swipe length" depletion

	// whether this Guardian is currently in a reload process
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammunition")
		bool isReloading;

	// time in seconds the reload process takes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammunition")
		float reloadTime;

	// time the Current Reload process has past
	UPROPERTY(BlueprintReadWrite, Category = "Ammunition")
		float reloadTimeCurrent;

	// temporarily stores the maximum amount of projectiles - because the maximum projectiles are used to display reload progress
	UPROPERTY(BlueprintReadWrite, Category = "Ammunition")
		float reloadTmpAmmoStore;

	// amount of maximum Taps necessary to Revive the Guardian, i.e. the target value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive Mechanic")
		int32 reviveTapsMaximum;

	// amount of initial Taps Revive Process begins with
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive Mechanic")
		int32 reviveTapsStart;

	// amount of current Taps of this Revive Process
	UPROPERTY(BlueprintReadWrite, Category = "Revive Mechanic")
		float reviveTapsCurrent; //in order to have smoother reduction/gains over time ->float

	// amount of Taps reduced/gained per second
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive Mechanic")
		int32 reviveTapsRemovedSecond;

	// whether Taps will be added or removed per second (put -1, 0 or 1 in here)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive Mechanic")
		int32 reviveTapsRemovedSecondMultiplier;

	// amount of Taps removed when hit via Enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive Mechanic")
		int32 reviveTapsRemovedEnemy;

	// Hitpoints the Guardian gets after the first Revive
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive Mechanic")
		int32 reviveHitpointsFirst;

	// Hitpoints the Guardian gets every additional Revive
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive Mechanic")
		int32 reviveHitpointsNext;

	// Additional Taps necessary for the next revive (added on Top of reviveTapsMaximum after each revive)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive Mechanic")
		int32 reviveTapsAdditional;

	// Flag to check whether the current revive is the first one
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive Mechanic")
		bool reviveIsFirst;

	// Flag to check whether the revive mechanic is currently active
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive Mechanic")
		bool reviveIsActive;

	// Flag to check whether the player failed to revive
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive Mechanic")
		bool isDead;
	
	// bool used to execute a red screen flash
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Feedback")
		bool doFlash;

	///
	///	UFUNCTIONS
	///

	// activates this guardian so that attacks can be performed with it -not used by now
	UFUNCTION(BlueprintCallable, Category = "UsabilityFunctions")
		void Activate(); // i am not sure whether the enemyType matters

	// deactivates this guardian so that no attacks can be performed with it -not used by now
	UFUNCTION(BlueprintCallable, Category = "UsabilityFunctions")
		void Deactivate(); // i am not sure whether the enemyType matters

	// Calculates new Hitpoints after Guardian is hit by enemy - if necessary will initialize Revive Mechanic
	UFUNCTION(BlueprintCallable, Category = "HitpointsFunctions")
		void GotHit(); // i am not sure whether the enemyType matters
	
	// trigger event to initialize the revive
	UFUNCTION(BlueprintImplementableEvent, Category = "HitpointsFunctions")
		void InitRevive(); // i am not sure whether the enemyType matters

	// trigger event for shotFeedback
	UFUNCTION(BlueprintImplementableEvent, Category = "FeedbackFunctions")
		void ShotFeedback(); 

	// trigger event for gotHitFeedback
	UFUNCTION(BlueprintImplementableEvent, Category = "FeedbackFunctions")
		void GotHitFeedback(); 


	// Assigns new Values when after a successful revive
	UFUNCTION(BlueprintCallable, Category = "HitpointsFunctions")
		void Revive();

	// calculates new revive tap current value every tick for smooth fill bar progress
	UFUNCTION(BlueprintCallable, Category = "HitpointsFunctions")
		void calculateReviveTapCurrent(float deltaSeconds);
	
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

	// will add +1 projectile
	UFUNCTION(BlueprintCallable, Category = "AmmunitionFunctions")
		void addProjectile();





	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	


	//FTimerHandle reloadTimerHandle;
	/*
	// will pause the reloadTimer
	UFUNCTION(BlueprintCallable, Category = "AmmunitionFunctions")
	void pauseReload();

	// will unPause the reloadTimer
	UFUNCTION(BlueprintCallable, Category = "AmmunitionFunctions")
	void unpauseReload();
	*/
	
};
