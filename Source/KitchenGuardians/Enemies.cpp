// Fill out your copyright notice in the Description page of Project Settings.

#include "KitchenGuardians.h"
#include "Enemies.h"


// Sets default values
AEnemies::AEnemies()
{
	// Sets default values for this actor's properties
	hitPoints = 3;
	baseScore = 100;
	jumpSpeed = 1;
	currentSpline = 0;
	distPerc = 0.0f;
	guardianHitCase = 1;

}

// Called when the game starts or when spawned
void AEnemies::BeginPlay()
{
	Super::BeginPlay();
}


void AEnemies::MoveEnemyAlongSpline()
{
	FVector newLocation = splineList[currentSpline]->GetWorldLocationAtDistanceAlongSpline(splineList[currentSpline]->GetSplineLength() * distPerc);
	SetActorLocation(newLocation, false);
}

void AEnemies::CalculateDistancePercentage(float deltaTime)
{
	float result;
	float zDirector = splineList[currentSpline]->GetWorldDirectionAtDistanceAlongSpline(splineList[currentSpline]->GetSplineLength() * distPerc).Z;
	result = ((((abs(cos(zDirector)) * 0.5f) + ((distPerc * 0.3f) + 0.02f)) * deltaTime) + distPerc);
	distPerc = result;
}

void AEnemies::CheckDistancePercentage()
{
	if (distPerc >= 1.0f)
	{
		if (currentSpline < (splineList.Num() - 1))
		{
			distPerc = 0.0f;
			currentSpline++;
			if (!isIdle)
			{

			}
			if (isIdle)
			{


			}

		}
		else
		{
			switch (guardianHitCase)
			{
				case 1:
					hitRice();
				break;
				case 2:
					hitToast();
					break;
				case 3:
					hitIce();
					break;
			}
			Destroy();
		}
	}
}

void AEnemies::spawnKnife(GuardianTypeEnum guardianType)
{

	switch (guardianType)
	{
	case GuardianTypeEnum::Toaster:
		knifeSpawn = guardianToast->GetTransform();
		guardianToast->Shot(-1);
		break;
	case GuardianTypeEnum::Ice:
		knifeSpawn = guardianIce->GetTransform();
		guardianIce->Shot(-1);
		break;
	}
	spawnKnifeExecute();
}

void AEnemies::GotHit(GuardianTypeEnum guardianType)
{
	int32 calculatedDamage;
	switch (guardianType)
	{
	case GuardianTypeEnum::Toaster:
		calculatedDamage = 9;
		break;
	case GuardianTypeEnum::Rice:
		calculatedDamage = 1;
		break;
	case GuardianTypeEnum::Ice:
		calculatedDamage = 1;
		break;
	}

	hitPoints -= calculatedDamage;
	if (hitPoints <= 0)
	{
		diedFeedback();
	}
	else
	{
		GotHitFeedback();
	}

}



