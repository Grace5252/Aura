// Copyright (c) Druid Mechanics, Grace Cappella


#include "AbilitySystem/Data/AttributeInfo.h"
#include "AuraLogChannels.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FAuraAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogAura, Error, TEXT("Can't Find Info for AttributeTag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(), *GetNameSafe(this));
	}

	return FAuraAttributeInfo();
}
