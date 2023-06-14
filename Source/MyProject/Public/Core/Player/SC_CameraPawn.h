// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SC_CameraPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USceneComponent;

UCLASS()
class MYPROJECT_API ASC_CameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASC_CameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	USceneComponent* SceneComponent;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera, meta = (ClampMin = "0", ClampMax = "100", AllowPrivateAccess = true))
	float MoveSpeedCamera = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera, meta = (ClampMin = "0", ClampMax = "100", AllowPrivateAccess = true))
	float SpeedZoomCamera = 0.f;

	FVector NextCameraLocation;
	float NextCameraZoomPosition = 0.f;
	float ThisDeltaTime = 0.f;
	bool IsCameraRotate = false;

	TWeakObjectPtr<APlayerController> PlayerController = nullptr;
	void MoveByCursor();
	
	void CameraMoveHorizontal(float Amount);
	void CameraMoveVertical(float Amount);
	void CameraZoom(float Amount);
	void StartCameraRotate();
	void StopCameraRotate();
	void CameraTurnX(float Amount);
	void CameraTurnY(float Amount);
};
