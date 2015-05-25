// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Classes/Components/SplineComponent.h"

#include "Spawn.generated.h"

UCLASS()
class KITCHENGUARDIANS_API ASpawn : public AActor
{
	GENERATED_BODY()
	
public:	


	///
	///	UPROPERTYS
	///


	// Spline Component List - one Route
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Route1")
		TArray<USplineComponent*> splineList;

	// Which Guardian the enemy on this route will be reducing hitpoints when reaching the end of this path
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Route1")
		uint8 guardianHitCase;



	///
	///	UFUNCTIONS
	///

	// Spawn an Enemy
	UFUNCTION(BlueprintCallable, Category = "EnemyFunctions")
		void Spawn(uint8 difficulty);

	// Sets default values for this actor's properties
	ASpawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
