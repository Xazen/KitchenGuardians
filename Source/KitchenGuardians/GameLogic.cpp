// Fill out your copyright notice in the Description page of Project Settings.

#include "KitchenGuardians.h"
#include "GameLogic.h"


// Sets default values
AGameLogic::AGameLogic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	highScore = 0;
	spawnTimeDelta = 2.5f;
}

void AGameLogic::AddScore(uint32 addedScore)
{
	highScore += addedScore;
}

//unfinished
uint32 AGameLogic::calculateScore(uint8 enemyType, uint8 attackType, int32 multiplier, int32 bonus)
{
	uint32 calculatedScore=0;

	//switch on enemy and attacktype
	//enum for enemytype may be better
	calculatedScore = enemyType *multiplier + bonus;

	return calculatedScore;
}

//unfinished - see function in spawncontr blueprint
float AGameLogic::newSpawnDeltaTime()
{
	float newSpawnDelta = spawnTimeDelta * 0.95f;
	return newSpawnDelta;

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

