// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AlterableObject.generated.h"

UCLASS()
class KITCHENGUARDIANS_API AAlterableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAlterableObject();

	///
	///	UPROPERTYS
	///

	// Boolean to prevent saving wrong actor position  
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reset")
	bool firstStart;

	// Start Position of Alterable Object
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reset")
	FVector startPosition;

	// Start Rotation of Alterable Object
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reset")
	FRotator startRotation;

	// Boolean to differentiate between early restart and when actor has been moved and/or rotated
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reset")
	bool physicsTriggered;
};
