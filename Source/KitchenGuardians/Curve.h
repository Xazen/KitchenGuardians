// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Classes/Components/SplineComponent.h"
#include "Curve.generated.h"

UCLASS()
class KITCHENGUARDIANS_API ACurve : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACurve();

	///
	///	UPROPERTYS
	///
	/** point light component */
	UPROPERTY(VisibleAnywhere, Category = "Spline Component")
	class USplineComponent* splineComponent;
	
};
