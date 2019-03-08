// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUp_Coin.h"
#include "BaseCharacter.h"

APickUp_Coin::APickUp_Coin()
{

}

void APickUp_Coin::CallectPickUp(class ABaseCharacter* Charcter)
{
	if (Role != ROLE_Authority) {
		return;
	}
	if (Charcter) {
		Charcter->CollectCoin();
		bIsPickedUp = true;
		this->Destroy();
	}

}
