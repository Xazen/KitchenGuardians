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
	playerNameList.Add("Player X");

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
				// return counter2++
				return counter2++;
				// break
				break;
			}
			if (j == 0)
			{
				highScoreList[j] = newScore;
				// return 1
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
