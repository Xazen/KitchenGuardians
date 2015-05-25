// Fill out your copyright notice in the Description page of Project Settings.

#include "KitchenGuardians.h"
#include "Guardian.h"


// Sets default values
AGuardian::AGuardian()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGuardian::BeginPlay()
{
	Super::BeginPlay();
	projectilesCurrent = projectilesMaximum;
	reviveTapsCurrent = reviveTapsStart;
}

// Called every frame
void AGuardian::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AGuardian::GotHit()
{
	if (isDead())
	{
		reviveTapsCurrent -= reviveTapsRemovedEnemy;
	}
	else{
		hitpoints -= 1;
		//if==0 initiate revivemechanic
	}

}

void AGuardian::Shot()
{
	projectilesCurrent -= 1;
}

bool AGuardian::canShoot()
{
	if (!activated)
		return false;
	if (hitpoints == 0)
		return false;
	if (projectilesCurrent == 0)
		return false;

	return true;

}

void AGuardian::Revive()
{
	if (reviveIsFirst)
	{
		reviveIsFirst = false;
		hitpoints = reviveHitpointsFirst;
	}
	else
	{
		hitpoints = reviveHitpointsNext;
	}
	reviveTapsCurrent = reviveTapsStart;

	reviveTapsMaximum += reviveTapsAdditional;
	//test
}

bool AGuardian::isDead()
{
	return hitpoints==0;
}


void AGuardian::Activate()
{
	activated = true;
}
void AGuardian::Deactivate()
{
	activated = false;
}
