// Copyright (c) Druid Mechanics, Grace Cappella


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AuraGameplayTags.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);

	for (auto& Tag : AttributeInfo.Get()->AttributeInformation)
	{
		BroadcastAttributeInfo(Tag.AttributeTag);
	}

	AAuraPlayerState* PS = CastChecked<AAuraPlayerState>(PlayerState);
	OnPlayerAttributePointsChangedDelegate.Broadcast(PS->GetAttributePoints());
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);

	for (auto& Tag : AttributeInfo.Get()->AttributeInformation)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Tag.AttributeGetter).AddLambda(
			[this, Tag](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Tag.AttributeTag);
			}
		);
	}

	AAuraPlayerState* PS = CastChecked<AAuraPlayerState>(PlayerState);
	PS->OnAttributePointsChangedDelegate.AddLambda(
		[this](int32 NewPoints)
		{
			OnPlayerAttributePointsChangedDelegate.Broadcast(NewPoints);
		}
	);
}

void UAttributeMenuWidgetController::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	AuraASC->UpgradeAttribute(AttributeTag);
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& Tag) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Tag);
	Info.AttributeValue = Info.AttributeGetter.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
