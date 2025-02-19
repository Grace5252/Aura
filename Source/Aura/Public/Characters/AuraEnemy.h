// Copyright (c) Druid Mechanics, Grace Cappella

#pragma once

#include "CoreMinimal.h"
#include "Characters/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();

	virtual void BeginPlay() override;

	/*Enemy Interface Functions*/
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	/*Combat Interface Functions*/
	virtual int32 GetPlayerLevel() override;

	/*Inherited Functions*/
	virtual void InitAbilityActorInfo() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
};
