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
	idleTime = 0.5f;
}

// Called when the game starts or when spawned
void AEnemies::BeginPlay()
{
	Super::BeginPlay();
}


void AEnemies::MoveEnemyAlongSpline()
{
	if (!isIdle)
	{
		FVector newLocation = splineList[currentSpline]->GetWorldLocationAtDistanceAlongSpline(splineList[currentSpline]->GetSplineLength() * distPerc);
		SetActorLocation(newLocation, false);
	}

}

void AEnemies::CalculateDistancePercentage(float deltaTime)
{
	if (!isIdle)
	{
		float result;
		float zDirector = splineList[currentSpline]->GetWorldDirectionAtDistanceAlongSpline(splineList[currentSpline]->GetSplineLength() * distPerc).Z;
		result = ((((abs(cos(zDirector)) * 0.5f) + ((distPerc * 0.3f) + 0.02f)) * deltaTime) + distPerc);
		distPerc = result;
	}
	else
	{
		idleCurrentTime += deltaTime;
	}

}

void AEnemies::CheckDistancePercentage()
{
	if (distPerc >= 1.0f)
	{
		if (currentSpline < (splineList.Num() - 1))
		{
			if (!isIdle)
			{
				isIdle = true;
				idleCurrentTime = 0;
			}
			if (isIdle)
			{
				if (idleCurrentTime >= idleTime)
				{
					distPerc = 0.0f;
					currentSpline++;
					isIdle = false;
				}

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

void AEnemies::spawnKnife(guardianTypeEnum guardianType)
{

	switch (guardianType)
	{
	case guardianTypeEnum::VE_Toaster:
		knifeSpawn = guardianToast->GetTransform();
		guardianToast->Shot(-1);
		break;
	case guardianTypeEnum::VE_Ice:
		knifeSpawn = guardianIce->GetTransform();
		guardianIce->Shot(-1);
		break;
	}
	spawnKnifeExecute();
}

void AEnemies::GotHit(guardianTypeEnum guardianType)
{
	int32 calculatedDamage;
	switch (guardianType)
	{
	case guardianTypeEnum::VE_Toaster:
		calculatedDamage = 9;
		break;
	case guardianTypeEnum::VE_Rice:
		calculatedDamage = 1;
		break;
	case guardianTypeEnum::VE_Ice:
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



