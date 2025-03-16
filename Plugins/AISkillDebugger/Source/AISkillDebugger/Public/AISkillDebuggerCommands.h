// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "AISkillDebuggerStyle.h"

class FAISkillDebuggerCommands : public TCommands<FAISkillDebuggerCommands>
{
public:

	FAISkillDebuggerCommands()
		: TCommands<FAISkillDebuggerCommands>(TEXT("AISkillDebugger"), NSLOCTEXT("Contexts", "AISkillDebugger", "AISkillDebugger Plugin"), NAME_None, FAISkillDebuggerStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};