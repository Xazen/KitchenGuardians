// Fill out your copyright notice in the Description page of Project Settings.

#include "KitchenGuardians.h"
#include "Enemies.h"


// Sets default values
AEnemies::AEnemies()
{
	// Sets default values for this actor's properties
	hitPoints = 0;
	baseDamage = 0;
	baseScore = 0;
	jumpSpeed = 0;
	currentSpline = 0;
	distPerc = 0.0f;
	botHitCase = 0;
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
	result = (((abs(cos(zDirector)) * 0.5f) + ((distPerc * 0.3f) + 0.02f) * deltaTime) + distPerc);
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
		}
		else
		{
			switch (botHitCase)
			{
				case 1:
					//guardianOne->GotHit();
					break;
				case 2: 
					//guardianTwo->GotHit();
					break;
				case 3: 
					//guardianThree->GotHit();
					break;
			}
			Destroy();
		}
	}
}

void AEnemies::GotHit(UParticleSystem *emitterTemplate, uint8 calculatedDamage)
{
	UGameplayStatics::SpawnEmitterAtLocation(this, emitterTemplate, GetActorLocation(), FRotator::ZeroRotator, true);
	hitPoints -= calculatedDamage;
	if (hitPoints <= 0)
	{
		// riceBot->PlaySoundAtLocation()
		// riceBot->Scorred(baseScore);
		Destroy();
	}
	else
	{
		// riceBot->PlaySoundAtLocation()
	}
}