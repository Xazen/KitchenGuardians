// Fill out your copyright notice in the Description page of Project Settings.

#include "KitchenGuardians.h"
#include "Enemies.h"


// Sets default values
AEnemies::AEnemies()
{
	// Sets default values for this actor's properties
	hitPoints = 3;
	baseScore = 100;
	speedFactor = 1;
	currentSpline = 0;
	distPerc = 0.0f;
	idleTime = 0.5f;
	isWalking = false;
	jumpLerp = 0.45f;
	baseSpeedJump = 1.0f;
	baseSpeedWalk = 1.0f;
	rotationLerpSpeed = 7.5f;
	isEnemyVulnerable = true;
	minGibbletImpulse = 30;
	maxGibbletImpulse = 120;
	dmgTap = 9;
	dmgSwipe = 1;
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
		if (!isWalking)
		{
			FVector newLocation = curveList[currentSpline]->splineComponent->GetWorldLocationAtDistanceAlongSpline(curveList[currentSpline]->splineComponent->GetSplineLength() * distPerc);
			SetActorLocation(newLocation, false);
			switch (enemyMoveType)
			{
			case EnemyMoveTypeEnum::Standard:

				break;
			case EnemyMoveTypeEnum::Tank:

				break;
			case EnemyMoveTypeEnum::Fast:

				break;
			}
		}
		else
		{
			FVector newLocation = curveList[currentSpline]->splineComponent->GetWorldLocationAtDistanceAlongSpline(curveList[currentSpline]->splineComponent->GetSplineLength() * distPerc);
			SetActorLocation(newLocation, false);
		}

	}

}

void AEnemies::Rotate(float deltaTime)
{
	if (isIdle)
	{
		FRotator enemyRot = GetActorRotation();
		FRotator targetRot = curveList[currentSpline + 1]->splineComponent->GetWorldRotationAtDistanceAlongSpline(0.0f);

		float t = deltaTime*rotationLerpSpeed;
		float v0 = enemyRot.Yaw;
		float v1 = targetRot.Yaw;
		float rotation = (1 - t)*v0 + t*v1;
		//float rotation = FMath::LerpStable(enemyRot.Yaw, targetRot.Yaw, deltaTime*rotationLerpSpeed); 
		FRotator newRot = FRotator(enemyRot.Pitch, rotation, enemyRot.Roll);
		SetActorRotation(newRot);
	}
	else
	{
		FRotator enemyRot = GetActorRotation();
		FRotator targetRot = curveList[currentSpline]->splineComponent->GetWorldRotationAtDistanceAlongSpline(curveList[currentSpline]->splineComponent->GetSplineLength() * distPerc);
		FRotator newRot = FRotator(enemyRot.Pitch, targetRot.Yaw, enemyRot.Roll);
		SetActorRotation(newRot);
	}
}

void AEnemies::CalculateDistancePercentage(float deltaTime)
{
	if (!isIdle)
	{
		float result;
		float zDirector = curveList[currentSpline]->splineComponent->GetWorldDirectionAtDistanceAlongSpline(curveList[currentSpline]->splineComponent->GetSplineLength() * distPerc).Z;
		if (!isWalking)
		{
			float adjustedTime = deltaTime*speedFactor*baseSpeedJump;
			float t = jumpLerp;
			float v0 = adjustedTime;
			float v1 = (sin(fabs(zDirector)) * adjustedTime);
			result = ((1 - t)*v0 + t*v1) + distPerc;
			//result = FMath::Lerp(adjustedTime,(sin(abs(zDirector)) * adjustedTime) , jumpLerp) + distPerc;
		}
		else
		{
			float adjustedTime = deltaTime*speedFactor*baseSpeedWalk;
			result = adjustedTime + distPerc;
		}

		distPerc = result;
	}
	else
	{
		idleCurrentTime += deltaTime;
	}

}

//return true if enemy has reached its goal
bool AEnemies::CheckDistancePercentage()
{
	if (distPerc >= 1.0f)
	{
		if (currentSpline < (curveList.Num() - 1))
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
					//isWalking = walkingList[currentSpline];
					isIdle = false;
				}


			}
			return false;
		}
		else
		{
			guardianToast->GotHit();
			hitToastFeedback();
			return true;
		}
	}
	return false;
}


void AEnemies::GotHit(GuardianTypeEnum guardianType)
{
	int32 calculatedDamage = 0;
	switch (guardianType)
	{
	case GuardianTypeEnum::Toaster:
		calculatedDamage = dmgTap;
		break;
	case GuardianTypeEnum::Rice:
		calculatedDamage = dmgSwipe;
		break;

	}
	if (isEnemyVulnerable)
	{
		hitPoints -= calculatedDamage;
		if (hitPoints <= 0)
		{
			//diedFeedback();
			switch (guardianType)
			{
			case GuardianTypeEnum::Toaster:
				diedToastFeedback();
				break;
			case GuardianTypeEnum::Rice:
				diedRiceFeedback();
				break;

			}
			
		}
		else
		{
			//GotHitFeedback();
			switch (guardianType)
			{
			case GuardianTypeEnum::Toaster:
				GotHitToastFeedback();
				break;
			case GuardianTypeEnum::Rice:
				GotHitRiceFeedback();
				break;

			}
		}
	}
	else
	{
		switch (guardianType)
		{
		case GuardianTypeEnum::Toaster:
			guardianToast->GotHit();
			break;
		case GuardianTypeEnum::Rice:
			guardianToast->GotHit();
			break;
		}
		gotHitInvulnerableFeedback();
	}

}

void AEnemies::AddGibbletImpulse2(UPrimitiveComponent* Gibblet)
{
	FVector force;
	force.X = FMath::RandRange(-1, 1) * FMath::RandRange(minGibbletImpulse, maxGibbletImpulse);
	force.Y = FMath::RandRange(-1, 1) * FMath::RandRange(minGibbletImpulse, maxGibbletImpulse);
	force.Z = FMath::RandRange(-1, 1) * FMath::RandRange(minGibbletImpulse, maxGibbletImpulse);
	Gibblet->AddImpulse(force,"None",true);
}

float AEnemies::calcDropShadowAlpha(float zDistance)
{
	//lerp?

	if (zDistance > 100)
		return 0.3f;

	if (zDistance > 80)
		return 0.4f;

	if (zDistance > 60)
		return 0.5f;

	if (zDistance > 40)
		return 0.6f;

	if (zDistance > 30)
		return 0.7f;

	if (zDistance > 20)
		return 0.8f;

	if (zDistance > 10)
		return 0.9f;

	return 1.0f;

}
