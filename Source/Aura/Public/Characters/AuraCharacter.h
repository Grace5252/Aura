// Copyright (c) Druid Mechanics, Grace Cappella

#pragma once

#include "CoreMinimal.h"
#include "Characters/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();

	void PossessedBy(AController* NewController) override;
	void OnRep_PlayerState() override;

	/*Combat Interface*/
	virtual int32 GetPlayerLevel() override;

	/*Inherited Functions*/
	virtual void InitAbilityActorInfo() override;

private:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;
};
