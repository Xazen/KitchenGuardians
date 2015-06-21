// Fill out your copyright notice in the Description page of Project Settings.

#include "KitchenGuardians.h"
#include "Curve.h"


// Sets default values
ACurve::ACurve()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Now this pointer need inside brackets
	splineComponent = CreateDefaultSubobject<USplineComponent>("SplineComponent");
	RootComponent = splineComponent;
}
