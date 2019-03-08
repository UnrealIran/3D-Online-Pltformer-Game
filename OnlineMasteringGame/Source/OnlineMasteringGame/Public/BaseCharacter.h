// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class ONLINEMASTERINGGAME_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditDefaultsOnly,Category="BaseCharcter")
		class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, Category = "BaseCharcter")
		class USpringArmComponent* SpringArm;

	UFUNCTION(BlueprintCallable, Category = "Base Charcter")
		void CollectCoin();

	UFUNCTION(BlueprintCallable, Category = "Base Charcter")
		void CollectHeart();
public:

	void MoveForward(float amount);

	void MoveRight(float Value);
	void RotateCamera(float Value);
	void ChangeCamerahight(float Value);

};
