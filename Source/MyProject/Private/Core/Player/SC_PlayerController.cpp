// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Player/SC_PlayerController.h"

ASC_PlayerController::ASC_PlayerController()
{
}

// Called when the game starts or when spawned
void ASC_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
}

// Called every frame
void ASC_PlayerController::Tick(float DeltaTime)
{
}