// Fill out your copyright notice in the Description page of Project Settings.

#include "KitchenGuardians.h"
#include "GameLogic.h"


// Sets default values
AGameLogic::AGameLogic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	highScore = 0;
	killCounterChillis = 0;
	killCounterMushrooms = 0;
	
	spawnTimeDelta = 2.5f;
	isGameover = false;
}

void AGameLogic::AddScore(int32 addedScore, enemyTypeEnum enemyType)
{
	highScore += addedScore;
	switch (enemyType)
	{
	case enemyTypeEnum::VE_Aubergine:
		killCounterOnions += 1;
		break;

	case enemyTypeEnum::VE_Chili:
		killCounterChillis += 1;
		break;

	case enemyTypeEnum::VE_Mushroom:
		killCounterMushrooms += 1;
		break;
	}


}

//unfinished
int32 AGameLogic::calculateScore(enemyTypeEnum enemyType, guardianTypeEnum guardianType, int32 multiplier, int32 bonus)
{
	int32 calculatedScore=0;

	//switch on enemy and guardiantype
	calculatedScore = 1.0f *multiplier + bonus;

	return calculatedScore;
}

//unfinished - see function in spawncontr blueprint
float AGameLogic::newSpawnDeltaTime()
{
	float newSpawnDelta = spawnTimeDelta * 0.95f;
	return newSpawnDelta;

}

void AGameLogic::gameOver()
{
	isGameover = true;
	gameOverExecute();
}


// Called when the game starts or when spawned
void AGameLogic::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameLogic::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

