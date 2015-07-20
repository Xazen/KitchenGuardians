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

	// Flag to check whether the player is Dead
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Feedback")
		bool isDead;
	

	///
	///	UFUNCTIONS
	///

	// Calculates new Hitpoints after Guardian is hit by enemy
	UFUNCTION(BlueprintCallable, Category = "HitpointsFunctions")
		void GotHit(); // i am not sure whether the enemyType matters
	
	// Will add Full Hitpoints
	UFUNCTION(BlueprintCallable, Category = "HitpointsFunctions")
		void Heal(); // i am not sure whether the enemyType matters

	// Trigger event for gotHitFeedback
	UFUNCTION(BlueprintImplementableEvent, Category = "FeedbackFunctions")
		void GotHitFeedback(); 

	// Trigger event for HealedFeedback
	UFUNCTION(BlueprintImplementableEvent, Category = "FeedbackFunctions")
		void HealedFeedback();

	// Trigger event for diedFeedback
	UFUNCTION(BlueprintImplementableEvent, Category = "FeedbackFunctions")
		void DiedFeedback();

	// Trigger SlowMo
	UFUNCTION(BlueprintImplementableEvent, Category = "FeedbackFunctions")
		void TriggerSlowMo();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
};
