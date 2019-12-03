// Fill out your copyright notice in the Description page of Project Settings.


#include "ShatteredCamera.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "ShatteredCharacter.h"

// Sets default values
AShatteredCamera::AShatteredCamera()
{
	// Setup main root
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1300.f;
	CameraBoom->RelativeRotation = FRotator(-45.f, 0.f, 0.f);
	CameraBoom->RelativeLocation = FVector(0, 0, 0);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

// Called when the game starts or when spawned
void AShatteredCamera::BeginPlay()
{
	Super::BeginPlay();

	//if( GEngine )
	//{
	//  GEngine->AddOnScreenDebugMessage( 0, 30.f, FColor::Red,  "Camera CPP in BeginPlay" );
	//}

	auto pWorld = GetWorld();
	APlayerController* PlayerController = Cast<APlayerController>(pWorld->GetFirstPlayerController());
	if (PlayerController)
	{
		FViewTargetTransitionParams TransitionParams;
		PlayerController->SetViewTarget(this, TransitionParams);
	}
	
}

// Called every frame
void AShatteredCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	TArray<AActor*> FoundPlayers;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("player0"), FoundPlayers);
	auto pWorld = GetWorld();
	//APlayerController* PlayerController = Cast<APlayerController>(pWorld->GetFirstLocalPlayerFromController());
	APlayerController* PlayerController = Cast<APlayerController>(FoundPlayers[0]);
	FVector Pos = GetActorLocation();
	Pos.Z += PlayerController->GetTargetLocation().Z;
	SetActorLocation(Pos);
	*/
	//SetActorLocation(PlayerController->GetTargetLocation());
}

