// Copyright (c) Druid Mechanics, Grace Cappella

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AuraGameplayTags.h"
#include "GameplayTagContainer.h"
#include "SpellMenuWidgetController.generated.h"

class UAuraUserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpellGlobeSelectedSignature, UAuraUserWidget*, SpellGlobeButton);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSpellGlobeEnableDisableSignature, bool, bSpendPointsButtonEnabled, bool, bEquipButtonEnabled);

struct FSelectedAbility
{
	FGameplayTag Ability = FGameplayTag();
	FGameplayTag Status = FGameplayTag();
};

/**
 * 
 */
UCLASS()
class AURA_API USpellMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UFUNCTION(BlueprintCallable, Category = "GAS | Spells Menu")
	void SelectSpellGlobe(UAuraUserWidget* SpellGlobeButton);

	UPROPERTY(BlueprintAssignable, Category = "GAS | Spells Menu")
	FOnSpellGlobeSelectedSignature OnSpellGlobeSelectedDelegate;

	//Called from blueprint when a button is selected
	UFUNCTION(BlueprintCallable, Category = "GAS | Spells Menu")
	void SpellGlobeEnableDisableButtons(const FGameplayTag& AbilityTag, const FGameplayTag& AbilityStatusTag);

	UPROPERTY(BlueprintAssignable, Category = "GAS | Spells Menu")
	FOnSpellGlobeEnableDisableSignature OnSpellGlobeEnableDisableDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS | Spells Menu")
	FOnPointsChangedSignature OnPlayerSpellPointsChangedDelegate;

private:
	//Overloaded function - Called by delegate natively when leveling up/the ability status has changed
	void SpellGlobeEnableDisableButtons(int32 InSpellPoints, const FGameplayTag& AbilityStatusTag);

	FSelectedAbility SelectedAbility = { FGameplayTag(), FAuraGameplayTags::Get().Abilities_Status_Locked};
	int32 CurrentSpellPoints = 0;
};
