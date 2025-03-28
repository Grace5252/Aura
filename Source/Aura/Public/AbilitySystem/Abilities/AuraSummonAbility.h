// Copyright (c) Druid Mechanics, Grace Cappella

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraSummonAbility.generated.h"

class AAuraCharacterBase;

/**
 * 
 */
UCLASS()
class AURA_API UAuraSummonAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocations();

	UFUNCTION(BlueprintPure, Category = "Summoning")
	TSubclassOf<AAuraCharacterBase> GetRandomMinionClass();

	UFUNCTION(BlueprintCallable, Category = "Summoning")
	AAuraCharacterBase* GetRandomMinionClassDefaultObject(TSubclassOf<AAuraCharacterBase> MinionClass);

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	int32 NumOfMinions = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	TArray<TSubclassOf<AAuraCharacterBase>> MinionClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	float MinSpawnDistance = 150.f;

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	float MaxSpawnDistance = 350.f;

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	float SpawnSpreadAngle = 90.f;

private:
	void LineTraceForChosenLocation(FVector& ChosenLocation);
};
