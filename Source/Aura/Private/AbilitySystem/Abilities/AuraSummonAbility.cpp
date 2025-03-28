// Copyright (c) Druid Mechanics, Grace Cappella


#include "AbilitySystem/Abilities/AuraSummonAbility.h"
#include "Characters/AuraCharacterBase.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpreadAngle / 2.f, FVector::UpVector);

	TArray<FVector> SpawnLocations;
	if (NumOfMinions < 1)
	{
		return SpawnLocations;
	}
	if (NumOfMinions == 1)
	{
		FVector ChosenSpawnLocation = Location + (Forward * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance));
		LineTraceForChosenLocation(ChosenSpawnLocation);

		SpawnLocations.Add(ChosenSpawnLocation);
		return SpawnLocations;
	}

	float DeltaAngleBetweenSpawns = SpawnSpreadAngle / NumOfMinions - 1;
	float Offset = DeltaAngleBetweenSpawns / 2.f;

	for (int i = 0; i < NumOfMinions; i++) {
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaAngleBetweenSpawns * i + Offset, FVector::UpVector);
		FVector ChosenSpawnLocation = Location + (Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance));
		LineTraceForChosenLocation(ChosenSpawnLocation);

		SpawnLocations.Add(ChosenSpawnLocation);
	}

	return SpawnLocations;
}

TSubclassOf<AAuraCharacterBase> UAuraSummonAbility::GetRandomMinionClass()
{
	int32 Selection = FMath::RandRange(0, MinionClasses.Num() - 1);
	return MinionClasses[Selection];
}

AAuraCharacterBase* UAuraSummonAbility::GetRandomMinionClassDefaultObject(TSubclassOf<AAuraCharacterBase> MinionClass)
{
	return MinionClass->GetDefaultObject<AAuraCharacterBase>();
}

void UAuraSummonAbility::LineTraceForChosenLocation(FVector& ChosenLocation)
{
	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, ChosenLocation + FVector(0.f, 0.f, 400.f), ChosenLocation - FVector(0.f, 0.f, 400.f), ECC_Visibility);
	if (Hit.bBlockingHit)
	{
		ChosenLocation = Hit.ImpactPoint;
	}
}
