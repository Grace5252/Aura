// Copyright (c) Druid Mechanics, Grace Cappella


#include "UI/WidgetController/SpellMenuWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "UI/Widgets/AuraUserWidget.h"
#include "Player/AuraPlayerState.h"
#include "AbilitySystem/Data/AbilityInfo.h"

void USpellMenuWidgetController::BroadcastInitialValues()
{
	BroadcastAbilityInfo();

	OnPlayerSpellPointsChangedDelegate.Broadcast(GetAuraPS()->GetSpellPoints());
}

void USpellMenuWidgetController::BindCallbacksToDependencies()
{
	GetAuraASC()->AbilityStatusChanged.AddLambda(
		[this](const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag) 
		{
			if (SelectedAbility.Ability.MatchesTagExact(AbilityTag))
			{
				SelectedAbility.Status = StatusTag;
				SpellGlobeEnableDisableButtons(CurrentSpellPoints, StatusTag);
			}


			if (AbilityInfo)
			{
				FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
				Info.StatusTag = StatusTag;
				AbilityInfoDelegate.Broadcast(Info);
			}
		}
	);

	GetAuraPS()->OnSpellPointsChangedDelegate.AddLambda(
		[this](int32 NewPoints)
		{
			OnPlayerSpellPointsChangedDelegate.Broadcast(NewPoints);
			CurrentSpellPoints = NewPoints;

			SpellGlobeEnableDisableButtons(CurrentSpellPoints, SelectedAbility.Status);
		}
	);
}

void USpellMenuWidgetController::SelectSpellGlobe(UAuraUserWidget* SpellGlobeButton)
{
	OnSpellGlobeSelectedDelegate.Broadcast(SpellGlobeButton);
}

void USpellMenuWidgetController::SpellGlobeEnableDisableButtons(const FGameplayTag& AbilityTag, const FGameplayTag& AbilityStatusTag)
{
	bool bEnableSpellPointsButton = false;
	bool bEnableEquipButton = false;

	int32 SpellPoints = GetAuraPS()->GetSpellPoints();

	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	
	if (AbilityStatusTag.MatchesTagExact(GameplayTags.Abilities_Status_Equipped) || AbilityStatusTag.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked))
	{
		bEnableEquipButton = true;
		if (SpellPoints > 0)
		{
			bEnableSpellPointsButton = true;
		}
	}

	if (AbilityStatusTag.MatchesTagExact(GameplayTags.Abilities_Status_Eligible))
	{
		if (SpellPoints > 0)
		{
			bEnableSpellPointsButton = true;
		}
	}

	OnSpellGlobeEnableDisableDelegate.Broadcast(bEnableSpellPointsButton, bEnableEquipButton);

	SelectedAbility.Ability = AbilityTag;
	SelectedAbility.Status = AbilityStatusTag;
}

void USpellMenuWidgetController::SpellGlobeEnableDisableButtons(int32 InSpellPoints, const FGameplayTag& AbilityStatusTag)
{
	bool bEnableSpellPointsButton = false;
	bool bEnableEquipButton = false;

	int32 SpellPoints = InSpellPoints;

	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();

	if (AbilityStatusTag.MatchesTagExact(GameplayTags.Abilities_Status_Equipped) || AbilityStatusTag.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked))
	{
		bEnableEquipButton = true;
		if (SpellPoints > 0)
		{
			bEnableSpellPointsButton = true;
		}
	}

	if (AbilityStatusTag.MatchesTagExact(GameplayTags.Abilities_Status_Eligible))
	{
		if (SpellPoints > 0)
		{
			bEnableSpellPointsButton = true;
		}
	}

	OnSpellGlobeEnableDisableDelegate.Broadcast(bEnableSpellPointsButton, bEnableEquipButton);
}
