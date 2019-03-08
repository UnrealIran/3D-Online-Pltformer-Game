// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUp_Health.h"
#include "GameFramework/Pawn.h"
#include "BaseCharacter.h"
APickUp_Health::APickUp_Health()
{

}

void APickUp_Health::CallectPickUp(class ABaseCharacter* Charcter)
{
	if(Role != ROLE_Authority) { return; }
	if (Charcter) 
	{
		Charcter->CollectHeart();
		bIsPickedUp = true;
		this->Destroy();
	}
}
