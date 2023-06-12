// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Player/SC_GameModeBase.h"
#include "Core/Player/SC_CameraPawn.h"
#include "Core/Player/SC_PlayerController.h"

ASC_GameModeBase::ASC_GameModeBase()
{
	DefaultPawnClass = ASC_CameraPawn::StaticClass();
	PlayerControllerClass = ASC_PlayerController::StaticClass();
}