// Fill out your copyright notice in the Description page of Project Settings.

#include "KitchenGuardians.h"
#include "Guardian.h"


// Sets default values
AGuardian::AGuardian()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	hitpoints = 2;
	projectilesMaximum = 20;
	projectilesCurrent = projectilesMaximum;
	isDead = false;
	doFlash = false;
	isReloading = false;
	reloadTime = 2.0f;
	reloadTimeCurrent = 0.0f;
}

// Called when the game starts or when spawned
void AGuardian::BeginPlay()
{
	Super::BeginPlay();
	projectilesCurrent = projectilesMaximum;
}

// Called every frame
void AGuardian::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}



void AGuardian::GotHit()
{
	
		hitpoints -= 1;
		if (hitpoints <= 0)
		{
			hitpoints = 0;
			DiedFeedback();
		}
		else
		{
			GotHitFeedback();
		}
		
}



void AGuardian::Shot(int32 ammoCost)
{
	ShotFeedback();
	projectilesCurrent -= ammoCost;
}

bool AGuardian::canShoot()
{
	if (hitpoints == 0)
		return false;
	if (isReloading)
		return false;
	if (projectilesCurrent == 0)
		return false;
	return true;

}

void AGuardian::reloadAmmo(float deltaSeconds)
{
	if (isReloading)
	{
		reloadTimeCurrent += deltaSeconds;
		projectilesCurrent = reloadTimeCurrent;
		if (reloadTimeCurrent >= reloadTime)
		{
			isReloading = false;
			projectilesMaximum = reloadTmpAmmoStore;
			projectilesCurrent = projectilesMaximum;
		}

	}
	else{
		if (projectilesCurrent == 0)
		{
			initReload();
		}
	}
}

void AGuardian::initReload()
{
	ReloadFeedback();
	isReloading = true;
	reloadTmpAmmoStore = projectilesMaximum;
	projectilesMaximum = reloadTime;
	reloadTimeCurrent = 0.0f;
}