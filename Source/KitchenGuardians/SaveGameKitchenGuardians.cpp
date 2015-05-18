// Fill out your copyright notice in the Description page of Project Settings.

#include "KitchenGuardians.h"
#include "SaveGameKitchenGuardians.h"


USaveGameKitchenGuardians::USaveGameKitchenGuardians(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	playerName = "Player X";
}

void USaveGameKitchenGuardians::AddFirstScore(int32 firstScore, FString newPlayerName)
{
	playerName = newPlayerName;
	highScoreList.Add(firstScore);
}

void USaveGameKitchenGuardians::SaveNewScore(int32 newScore)
{
	bool valueIsInArray = false;
	uint8 listSize = highScoreList.Num();

	//
	for (int i = 0; i < listSize; i++)
	{
		if (highScoreList[i] == newScore)
		{
			valueIsInArray = true;
			break;
		}
	}

	// Array index out of bounds : -1 from an array of size 3
	if (!valueIsInArray)
	{
		// UE4 Add empty item for ordering list
		highScoreList.Add(0);

		listSize = highScoreList.Num() - 1;
		for (int j = listSize; j >= 0; j--)
		{
			if (highScoreList[j] < newScore)
			{
				if(j != 0)
				{
					int counter1 = j - 1;
					highScoreList[j] = highScoreList[counter1];
				}
			}
			else
			{
				int counter2 = j + 1;
				highScoreList[counter2] = newScore;
				break;
			}
			if (j == 0)
			{
				highScoreList[j] = newScore;
				break;
			}
		}
	}

}

