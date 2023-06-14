// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Player/SC_CameraPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ASC_CameraPawn::ASC_CameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<UStaticMeshComponent>("DefaultSceneRootComponent");
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->TargetArmLength = 700.f;
	SpringArmComponent->SetupAttachment(SceneComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ASC_CameraPawn::BeginPlay()
{
	Super::BeginPlay();

	NextCameraLocation = GetActorLocation();
	NextCameraZoomPosition = SpringArmComponent->TargetArmLength;
	PlayerController = Cast<APlayerController>(GetController());
	
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
}

// Called every frame
void ASC_CameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// MoveByCursor();
}

// Called to bind functionality to input
void ASC_CameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("CameraMoveHorizontal", this, &ASC_CameraPawn::CameraMoveHorizontal);
	PlayerInputComponent->BindAxis("CameraMoveVertical", this, &ASC_CameraPawn::CameraMoveVertical);
	PlayerInputComponent->BindAxis("CameraZoom", this, &ASC_CameraPawn::CameraZoom);
	PlayerInputComponent->BindAxis("CameraTurnX", this, &ASC_CameraPawn::CameraTurnX);
	PlayerInputComponent->BindAxis("CameraTurnY", this, &ASC_CameraPawn::CameraTurnY);
	PlayerInputComponent->BindAction("CameraRotate", IE_Pressed, this, &ASC_CameraPawn::StartCameraRotate);
	PlayerInputComponent->BindAction("CameraRotate", IE_Released, this, &ASC_CameraPawn::StopCameraRotate);
}
void ASC_CameraPawn::MoveByCursor()
{
	float MouseX, MouseY;
	PlayerController->GetMousePosition(MouseX, MouseY);
	
	const FVector2d ViewportSize = FVector2d(GEngine->GameViewport->Viewport->GetSizeXY());
	constexpr float BorderSize = 10.f;
	
	if (MouseX < BorderSize)
	{
		CameraMoveHorizontal(-1);
	}
	else if (MouseX > ViewportSize.X - BorderSize)
	{
		CameraMoveHorizontal(1);
	}
	
	if (MouseY < BorderSize)
	{
		CameraMoveVertical(1);
	}
	else if (MouseY > ViewportSize.Y - BorderSize)
	{
		CameraMoveVertical(-1);
	}
}

void ASC_CameraPawn::CameraMoveHorizontal(float Amount)
{
	ThisDeltaTime = GetWorld()->GetDeltaSeconds();
	NextCameraLocation += Amount * MoveSpeedCamera * GetActorRightVector();
	const FVector NewCameraLocation = FMath::VInterpTo(GetActorLocation(), NextCameraLocation, ThisDeltaTime, 2);
	SetActorLocation(NewCameraLocation);
}

void ASC_CameraPawn::CameraMoveVertical(float Amount)
{
	ThisDeltaTime = GetWorld()->GetDeltaSeconds();
	const FVector ForwardVector = GetActorForwardVector().GetSafeNormal();
	const FVector FlatForwardVector = FVector(ForwardVector.X, ForwardVector.Y, 0.f).GetSafeNormal();
	NextCameraLocation += Amount * MoveSpeedCamera * FlatForwardVector;
	const FVector NewCameraLocation = FMath::VInterpTo(GetActorLocation(), NextCameraLocation, ThisDeltaTime, 2);
	SetActorLocation(NewCameraLocation);
}

void ASC_CameraPawn::CameraZoom(float Amount)
{
	ThisDeltaTime = GetWorld()->GetDeltaSeconds();
	NextCameraZoomPosition = Amount * SpeedZoomCamera * SpringArmComponent->TargetArmLength;
	const float NewCameraZoomPosition = SpringArmComponent->TargetArmLength + NextCameraZoomPosition;
	SpringArmComponent->TargetArmLength = FMath::FInterpTo(SpringArmComponent->TargetArmLength, FMath::Clamp(NewCameraZoomPosition, 1000.f, 4000.f), ThisDeltaTime, 10);
}

void ASC_CameraPawn::StartCameraRotate()
{
	IsCameraRotate = true;
}

void ASC_CameraPawn::StopCameraRotate()
{
	IsCameraRotate = false;
}

void ASC_CameraPawn::CameraTurnX(float Amount)
{
	if (IsCameraRotate)
	{
		AddControllerYawInput(Amount);
	}
}

void ASC_CameraPawn::CameraTurnY(float Amount)
{
	if (IsCameraRotate)
	{
		AddControllerPitchInput(Amount);
	}
}

