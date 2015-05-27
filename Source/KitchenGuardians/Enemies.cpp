// Fill out your copyright notice in the Description page of Project Settings.

#include "KitchenGuardians.h"
#include "Enemies.h"


// Sets default values
AEnemies::AEnemies()
{
	// Sets default values for this actor's properties
	hitPoints = 3;
	baseDamage = 1;
	baseScore = 100;
	jumpSpeed = 1;
	currentSpline = 0;
	distPerc = 0.0f;
	guardianHitCase = 0;

}

// Called when the game starts or when spawned
void AEnemies::BeginPlay()
{
	Super::BeginPlay();
	GotHit(0);
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
			switch (guardianHitCase)
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

void AEnemies::GotHit(uint8 calculatedDamage)
{
	hitPoints -= calculatedDamage;
	UParticleSystem *emitterTemplate = nullptr; //unsicher: parameterübergabe?
	if (hitPoints <= 0)
	{
		DiedEffect(emitterTemplate); //unsicher: parameter?

		// riceBot->Scorred(baseScore);
		Destroy();
	}
	else
	{
		GotHitEffect(emitterTemplate); //unsicher: parameter?
	}
}

void AEnemies::GotHitEffect(UParticleSystem *emitterTemplate)
{
	UGameplayStatics::SpawnEmitterAtLocation(this, emitterTemplate, GetActorLocation(), FRotator::ZeroRotator, true);
		// riceBot->PlaySoundAtLocation()
}

void AEnemies::DiedEffect(UParticleSystem *emitterTemplate)
{
	UGameplayStatics::SpawnEmitterAtLocation(this, emitterTemplate, GetActorLocation(), FRotator::ZeroRotator, true);
	// riceBot->PlaySoundAtLocation()
}