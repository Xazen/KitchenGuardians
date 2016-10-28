// Fill out your copyright notice in the Description page of Project Settings.

#include "KitchenGuardians.h"
#include "Guardian.h"


// Sets default values
AGuardian::AGuardian()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	hitpoints = 2;
	isDead = false;
}

// Called when the game starts or when spawned
void AGuardian::BeginPlay()
{
	Super::BeginPlay();
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

void AGuardian::Heal()
{

	if (hitpoints == 1)
	{
		hitpoints++;
		HealedFeedback();
	}


}