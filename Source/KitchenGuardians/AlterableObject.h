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

	// Start Position of Alterable Object
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reset")
	FVector startPosition;

	// Start Rotation of Alterable Object
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reset")
	FRotator startRotation;

	// Called when the level reset function was called
	//virtual void Reset() override;
};
