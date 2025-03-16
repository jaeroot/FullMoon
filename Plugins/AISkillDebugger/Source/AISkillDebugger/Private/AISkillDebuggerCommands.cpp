// Copyright Epic Games, Inc. All Rights Reserved.

#include "AISkillDebuggerCommands.h"

#define LOCTEXT_NAMESPACE "FAISkillDebuggerModule"

void FAISkillDebuggerCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "AISkillDebugger", "Bring up AISkillDebugger window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
