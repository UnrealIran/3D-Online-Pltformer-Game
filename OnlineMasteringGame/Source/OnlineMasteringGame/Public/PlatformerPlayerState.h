// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlatformerPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEMASTERINGGAME_API APlatformerPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	APlatformerPlayerState();
	UFUNCTION(BlueprintCallable, Category = "Player State")
		void CollectCoin();

	UFUNCTION(BlueprintCallable, Category = "Player State")
		void CollectHeart();

protected:
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Platformer playe State")
		int NumberOfCoinsCollected;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Platformer playe State")
		int CurrentHealth;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Platformer playe State")
		int NumberOfDeathes;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "Platformer playe State")
		int MaxHealth;



};
