// Copyright (c) Druid Mechanics, Grace Cappella


#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

AAuraPlayerState::AAuraPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAuraPlayerState, Level);
	DOREPLIFETIME(AAuraPlayerState, XP);
	DOREPLIFETIME(AAuraPlayerState, AttributePoints);
	DOREPLIFETIME(AAuraPlayerState, SpellPoints);
}

void AAuraPlayerState::SetLevel(int32 NewLevel)
{
	Level = NewLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAuraPlayerState::AddToLevel(int32 AddedLevel)
{
	Level += AddedLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAuraPlayerState::SetXP(int32 NewXP)
{
	XP = NewXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AAuraPlayerState::AddToXP(int32 AddedXP)
{
	XP += AddedXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AAuraPlayerState::AddToAttributePoints(int32 AddedPoints)
{
	AttributePoints += AddedPoints;
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AAuraPlayerState::AddToSpellPoints(int32 AddedPoints)
{
	SpellPoints += AddedPoints;
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}

void AAuraPlayerState::OnRep_AttributePoints(int32 OldPoints)
{
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AAuraPlayerState::OnRep_SpellPoints(int32 OldPoints)
{
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}

void AAuraPlayerState::OnRep_Level(int32 OldLevel)
{
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAuraPlayerState::OnRep_XP(int32 OldXP)
{
	OnXPChangedDelegate.Broadcast(XP);
}
