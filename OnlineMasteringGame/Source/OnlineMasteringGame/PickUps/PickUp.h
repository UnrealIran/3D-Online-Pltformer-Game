// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUp.generated.h"

UCLASS()
class ONLINEMASTERINGGAME_API APickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUp();

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
		class USphereComponent* CollisionSphere;

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
		float SpinsPerSoconds;



	UFUNCTION()
	void OnComponentOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//Server Function called when actually pickup
	UFUNCTION(Server, WithValidation, Reliable, Category = "PickUp")
		virtual void CallectPickUp(class ABaseCharacter* Charcter);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Replicated)
		bool bIsPickedUp;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
