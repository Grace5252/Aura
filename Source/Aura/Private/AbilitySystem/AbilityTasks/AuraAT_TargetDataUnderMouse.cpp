// Copyright (c) Druid Mechanics, Grace Cappella


#include "AbilitySystem/AbilityTasks/AuraAT_TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"

UAuraAT_TargetDataUnderMouse* UAuraAT_TargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
    UAuraAT_TargetDataUnderMouse* MyObj = NewAbilityTask<UAuraAT_TargetDataUnderMouse>(OwningAbility);
    return MyObj;
}

void UAuraAT_TargetDataUnderMouse::Activate()
{
    const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
    if (bIsLocallyControlled) //We are on the client, so send target data up
    {
        SendMouseCursorData();
    }
    else //We are on the server, so listen for target data
    {
        AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(), GetActivationPredictionKey()).AddUObject(this, &UAuraAT_TargetDataUnderMouse::OnTargetDataReplicatedCallback);
        const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(GetAbilitySpecHandle(), GetActivationPredictionKey());
        if (!bCalledDelegate)
        {
            SetWaitingOnRemotePlayerData();
        }
    }

}

void UAuraAT_TargetDataUnderMouse::SendMouseCursorData()
{
    FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());

    APlayerController* PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get();
    FHitResult CursorHit;
    PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

    FGameplayAbilityTargetDataHandle DataHandle;
    FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
    Data->HitResult = CursorHit;
    DataHandle.Add(Data);

    AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey(), DataHandle, FGameplayTag(), AbilitySystemComponent->ScopedPredictionKey);

    if (ShouldBroadcastAbilityTaskDelegates())
    {
        ValidData.Broadcast(DataHandle);
    }
}

void UAuraAT_TargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag)
{
    AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());

    if (ShouldBroadcastAbilityTaskDelegates())
    {
        ValidData.Broadcast(DataHandle);
    }
}
