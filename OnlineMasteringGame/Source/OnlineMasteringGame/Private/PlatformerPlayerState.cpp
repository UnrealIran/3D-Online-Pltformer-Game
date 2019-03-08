// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformerPlayerState.h"
#include "UnrealNetwork.h"

APlatformerPlayerState::APlatformerPlayerState()
{
	NumberOfCoinsCollected = 0;
	MaxHealth = 3;

	CurrentHealth = MaxHealth;
	NumberOfDeathes = 0;

}

void APlatformerPlayerState::CollectCoin()
{
	NumberOfCoinsCollected += 1;
}

void APlatformerPlayerState::CollectHeart()
{
	CurrentHealth += 1;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);
}

void APlatformerPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APlatformerPlayerState, NumberOfCoinsCollected);
	DOREPLIFETIME(APlatformerPlayerState, CurrentHealth);
	DOREPLIFETIME(APlatformerPlayerState, NumberOfDeathes);
}