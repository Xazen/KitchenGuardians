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
	RadialForcePosition = FVector(0, 0, 0);
	triggerSlowMoPercentage = 0.95f;
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

		//old
		float t = deltaTime*rotationLerpSpeed;
		float v0 = enemyRot.Yaw;
		float v1 = targetRot.Yaw;
		float rotation = (1 - t)*v0 + t*v1;

		//new
		FRotator enemyYaw = FRotator(0, enemyRot.Yaw, 0);
		FRotator targetYaw = FRotator(0, targetRot.Yaw, 0);
		FRotator DeltaYaw = targetYaw - enemyYaw;
		DeltaYaw.Normalize();
		
		//float rotation = FMath::LerpStable(enemyRot.Yaw, targetRot.Yaw, deltaTime*rotationLerpSpeed); 
		FRotator newRot = FRotator(enemyRot.Pitch, enemyRot.Yaw+deltaTime*rotationLerpSpeed*DeltaYaw.Yaw, enemyRot.Roll);
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
		float currentSplinePosition = (curveList[currentSpline]->splineComponent->GetSplineLength())*distPerc;
		float splineLength = curveList[currentSpline]->splineComponent->GetSplineLength();
		if (!isWalking)
		{
			float adjustedTime = deltaTime*speedFactor*baseSpeedJump;
			float t = jumpLerp;
			float v0 = adjustedTime;
			float v1 = (sin(fabs(zDirector)) * adjustedTime);
			result = (((1 - t)*v0 + t*v1) +  currentSplinePosition) / splineLength;
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
				if (idleList.Num() == curveList.Num() || idleList.Num() == curveList.Num()-1)
				{
					idleTime = idleList[currentSpline];
				}
				idleCurrentTime = 0;
			}
			if (isIdle)
			{
				if (idleCurrentTime >= idleTime)
				{
					distPerc = 0.0f;
					currentSpline++;
					if (walkingList.Num() == curveList.Num())
					{
						isWalking = walkingList[currentSpline];
					}
					else
					{
						isWalking = false;
					}
					
					isIdle = false;
				}


			}
			return false;
		}
		else
		{
			if (guardianHitCaseEnum == GuardianTypeEnum::Toaster)
			{
				guardianToast->GotHit();
				hitToastFeedback();
				return true;
			}
			else
			{
				ReachedEndAsBonusEnemy();
			}

		}
	}
	if (distPerc >= triggerSlowMoPercentage&&currentSpline == (curveList.Num() - 1))
	{
		guardianToast->TriggerSlowMo();
	}
	return false;
}


void AEnemies::GotHit(AttackTypeEnum attackType, FVector HitLocation)
{
	if (attackType == AttackTypeEnum::Special)
	{
		hitPoints -= dmgTap;
		if (hitPoints <= 0)
		{
			RadialForcePosition = HitLocation;
			diedToastFeedback();
		}
		return;
	}

	if (isEnemyVulnerable)
	{
		switch (attackType)
		{
		case AttackTypeEnum::Tap:

			hitPoints -= dmgTap;
			if (hitPoints <= 0)
			{
				RadialForcePosition = HitLocation;
				diedToastFeedback();
			}
			else
			{
				GotHitToastFeedback();
			}
			break;
		case AttackTypeEnum::Swipe:
			hitPoints -= dmgSwipe;
			if (hitPoints <= 0)
			{
				diedRiceFeedback();
			}
			else
			{
				GotHitRiceFeedback();
			}
			break;
		}
	} 
	else
	{
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
