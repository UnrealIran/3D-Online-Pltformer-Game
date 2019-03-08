// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUps/PickUp.h"
#include "PickUp_Coin.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEMASTERINGGAME_API APickUp_Coin : public APickUp
{
	GENERATED_BODY()
public:

	APickUp_Coin();

	virtual void CallectPickUp(class ABaseCharacter* Charcter) override;
};
