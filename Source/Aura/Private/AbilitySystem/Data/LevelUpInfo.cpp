// Copyright (c) Druid Mechanics, Grace Cappella


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(const int32 xpAmount) const
{
	for (int32 i = 1; i < LevelUpInformation.Num(); i++)
	{
		if (xpAmount < LevelUpInformation[i].LevelUpRequirement)
			return i;
	}

	return 1;
}
