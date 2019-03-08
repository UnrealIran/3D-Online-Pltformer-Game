// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "PlatformerPlayerState.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Set up our springarm to hold our camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("Camera Boom"));
	//Do not allow spring arm to rotate with character
	SpringArm->bUsePawnControlRotation = false;
	//Do not allow it to be affected by relative rotation of character
	SpringArm->bAbsoluteRotation = true;
	//Length of arm
	SpringArm->TargetArmLength = 700.f;
	//Attach to root
	SpringArm->SetupAttachment(RootComponent);

	//Set up the camera
	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	//Give it a wider FOV
	Camera->FieldOfView = 110.f;
	//attach to SpringArm
	Camera->SetupAttachment(SpringArm);
	
	//set up basic network replication
	bReplicates = true;
	bAlwaysRelevant = true;
	bReplicateMovement = true;

	//Set up character movement properties

	//rotate the character in the direction its moving
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//don't rotate based on controller input
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//Set up some movement properties for improving input feel
	//jump higher
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	//fall faster
	GetCharacterMovement()->GravityScale = 2.f;
	//Allow some control of character while airborne
	GetCharacterMovement()->AirControl = 0.8f;



}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	//set the spring arm behind our character
	SpringArm->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0, -25, 180)));
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Bind Action
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ABaseCharacter::Jump);
// 	PlayerInputComponent->BindAction("UsePoweUps", EInputEvent::IE_Pressed, &ABaseCharacter::USePwerUps);
// 	PlayerInputComponent->BindAction("ShowPlayerScreen", EInputEvent::IE_Pressed, &ABaseCharacter::);
// 	PlayerInputComponent->BindAction("StartMenu", EInputEvent::IE_Pressed, &ABaseCharacter::Jump);
	//Bind Axis
 	PlayerInputComponent->BindAxis("MoveForward",this,&ABaseCharacter::MoveForward);
 	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
 	PlayerInputComponent->BindAxis("RotateCamera",this, &ABaseCharacter::RotateCamera);
 	PlayerInputComponent->BindAxis("ChangeCameraHieght", this, &ABaseCharacter::ChangeCamerahight);
}

void ABaseCharacter::MoveForward(float amount)
{
	FVector ForwardVector=SpringArm->GetForwardVector();
	this->AddMovementInput(ForwardVector, amount);
}
void ABaseCharacter::MoveRight(float amount)
{
	FVector RightVector = SpringArm->GetRightVector();
	this->AddMovementInput(RightVector, amount);

}
void ABaseCharacter::RotateCamera(float amount) 
{
	if (Controller && amount) {
		FVector rot = SpringArm->GetComponentRotation().Euler();
		rot += FVector(0, 0, amount);
		SpringArm->SetWorldRotation(FQuat::MakeFromEuler(rot));

	}
}
void ABaseCharacter::ChangeCamerahight(float amount)
{
	if (Controller && amount)
	{
		FVector rot = SpringArm->GetComponentRotation().Euler();
		float originalHeight = rot.Y;
		originalHeight += amount;
		originalHeight = FMath::Clamp(originalHeight, -45.f, -5.f);

		rot = FVector(0, originalHeight, rot.Z);
		SpringArm->SetWorldRotation(FQuat::MakeFromEuler(rot));
	}

}
void ABaseCharacter::CollectCoin()
{
	

	APlatformerPlayerState* PS = Cast<APlatformerPlayerState>(GetPlayerState());
	if (PS) {
		PS->CollectCoin();
	}

}

void ABaseCharacter::CollectHeart()
{
	APlatformerPlayerState* PS = Cast<APlatformerPlayerState>(GetPlayerState());
	if (PS) {
		PS->CollectHeart();
	}
}
