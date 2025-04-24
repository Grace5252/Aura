// Copyright (c) Druid Mechanics, Grace Cappella

#pragma once

#include "CoreMinimal.h"
#include "Characters/AuraCharacterBase.h"
#include "Interaction/PlayerInterface.h"
#include "AuraCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase, public IPlayerInterface
{
	GENERATED_BODY()

public:
	AAuraCharacter();

	void PossessedBy(AController* NewController) override;
	void OnRep_PlayerState() override;

	/*Player Interface*/
	virtual void AddToXP_Implementation(int32 InXP) override;

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
