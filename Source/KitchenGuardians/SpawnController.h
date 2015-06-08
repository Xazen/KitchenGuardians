// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
//#include "Classes/Components/SplineComponent.h"

#include "SpawnController.generated.h"

// Enums
UENUM(BlueprintType)
enum class EnemySpawnPointsEnum : uint8
{
	Fridge,
	Microwave,
	Stove,
	UpperWall
};


UCLASS()
class KITCHENGUARDIANS_API ASpawnController : public AActor
{
	GENERATED_BODY()

public:

	///
	///	UPROPERTYS
	///

	// Empty

	///
	///	UFUNCTIONS
	///

	// Sets default values for this actor's properties
	ASpawnController();

	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

	// Called every frame
	//virtual void Tick(float DeltaSeconds) override;

};
