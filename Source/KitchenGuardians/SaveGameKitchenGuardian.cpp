// Fill out your copyright notice in the Description page of Project Settings.

#include "KitchenGuardians.h"
#include "SaveGameKitchenGuardian.h"


USaveGameKitchenGuardian::USaveGameKitchenGuardian(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void USaveGameKitchenGuardian::AddFirstScore(int32 firstScore)
{
	highScoreList.Add(firstScore);
	playerNameList.Add("Player X");
}

int32 USaveGameKitchenGuardian::SaveNewScoreAndReturnIndex(int32 newScore)
{
	// Add new Element to playerNameList
	playerNameList.Add("Player X");

	bool valueIsInArray = false;
	uint8 listSize = highScoreList.Num();

	// Check if newScore is already in highScoreList
	for (int i = 0; i < listSize; i++)
	{
		if (highScoreList[i] == newScore)
		{
			valueIsInArray = true;
			return 0;
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
					int32 counter1 = j - 1;
					highScoreList[j] = highScoreList[counter1];
					// Move Playernames, too
					playerNameList[j] = playerNameList[counter1];
				}
			}
			else
			{
				int32 counter2 = j + 1;
				highScoreList[counter2] = newScore;
				// return counter2++
				return (counter2 + 1);
				// break
				break;
			}
			if (j == 0)
			{
				highScoreList[j] = newScore;
				// Set playername from old tier 1 to second tier
				playerNameList[1] = playerNameList[0];
				// return 1 or 2???
				return 1;
				// break
				break;
			}
		}
	}

	return 0;

}

void USaveGameKitchenGuardian::ChangePlayerName(int32 listIndex, FString newPlayerName)
{
	playerNameList[listIndex] = newPlayerName;
}
