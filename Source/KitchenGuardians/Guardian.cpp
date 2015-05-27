// Fill out your copyright notice in the Description page of Project Settings.

#include "KitchenGuardians.h"
#include "Guardian.h"


// Sets default values
AGuardian::AGuardian()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	activated = true;
	hitpoints = 2;
	projectilesMaximum = 20;
	projectilesCurrent = projectilesMaximum;
	reviveTapsMaximum = 20;
	reviveTapsStart = 5;
	reviveTapsRemovedSecond = 1;
	reviveTapsRemovedSecondMultiplier = 1;
	reviveTapsRemovedEnemy = 5;
	reviveHitpointsFirst = 2;
	reviveHitpointsNext = 1;
	reviveTapsAdditional = 5;
	reviveIsFirst = true;
	projectilesRefillTime = 3.0f;
}

// Called when the game starts or when spawned
void AGuardian::BeginPlay()
{
	Super::BeginPlay();
	projectilesCurrent = projectilesMaximum;
	reviveTapsCurrent = reviveTapsStart;
	GetWorld()->GetTimerManager().SetTimer(reloadTimerHandle, this, &AGuardian::GotHit, projectilesRefillTime, true, (-1.0f));
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::White, TEXT("reload"));
}

// Called every frame
void AGuardian::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AGuardian::GotHit()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::White, TEXT("THIS is PATRICK!"));


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

void AGuardian::pauseReload()
{
	GetWorld()->GetTimerManager().PauseTimer(reloadTimerHandle);

}

void AGuardian::unpauseReload()
{
	GetWorld()->GetTimerManager().UnPauseTimer(reloadTimerHandle);
}

void AGuardian::addProjectile()
{
	projectilesCurrent++;
	if (projectilesCurrent > projectilesMaximum)
		projectilesCurrent = projectilesMaximum;
}