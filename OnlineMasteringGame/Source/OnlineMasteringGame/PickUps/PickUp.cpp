// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUp.h"
#include "UnrealNetwork.h"
#include "BaseCharacter.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
APickUp::APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionSphere = CreateDefaultSubobject<USphereComponent>("CollsionSphere");
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionSphere->SetGenerateOverlapEvents(true);
	CollisionSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APickUp::OnComponentOverlap);
	RootComponent = CollisionSphere;
	CollisionSphere->SetIsReplicated(true);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetIsReplicated(true);

	SpinsPerSoconds = .5;

	bIsPickedUp = false;

	bReplicates = true;
	bAlwaysRelevant = true;
}
void APickUp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APickUp, bIsPickedUp);
	
}

void APickUp::OnComponentOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* Charcter = Cast<ABaseCharacter>(OtherActor);
	if (Charcter) {
		CallectPickUp(Charcter);
	}

}

void APickUp::CallectPickUp_Implementation(class ABaseCharacter* Charcter)
{
	if (Role != ROLE_Authority) {
		return;
	}
	bIsPickedUp = true;
}

bool APickUp::CallectPickUp_Validate(class ABaseCharacter* Charcter)
{
	return true;
}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//If not Picked up ,Spin COnstantly
	if (!bIsPickedUp)
	{
		float SpinThisFrame = (DeltaTime*SpinsPerSoconds) * 360;
		FVector rotation = RootComponent->GetComponentRotation().Euler();
		rotation += FVector(0, 0, SpinThisFrame);
		RootComponent->SetWorldRotation(FQuat::MakeFromEuler(rotation));

	}
}

