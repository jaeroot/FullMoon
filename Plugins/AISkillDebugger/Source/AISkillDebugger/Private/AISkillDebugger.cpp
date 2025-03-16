// Copyright Epic Games, Inc. All Rights Reserved.

#include "AISkillDebugger.h"
#include "AISkillDebuggerStyle.h"
#include "AISkillDebuggerCommands.h"
#include "EngineUtils.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "Widgets/SAISkillDebuggerMenu.h"

static const FName AISkillDebuggerTabName("AISkillDebugger");

#define LOCTEXT_NAMESPACE "FAISkillDebuggerModule"

void FAISkillDebuggerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FAISkillDebuggerStyle::Initialize();
	FAISkillDebuggerStyle::ReloadTextures();

	FAISkillDebuggerCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FAISkillDebuggerCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FAISkillDebuggerModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAISkillDebuggerModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(AISkillDebuggerTabName, FOnSpawnTab::CreateRaw(this, &FAISkillDebuggerModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FAISkillDebuggerTabTitle", "AISkillDebugger"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FAISkillDebuggerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FAISkillDebuggerStyle::Shutdown();

	FAISkillDebuggerCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AISkillDebuggerTabName);
}

TSharedRef<SDockTab> FAISkillDebuggerModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SAISkillDebuggerMenu)
		];
}

void FAISkillDebuggerModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(AISkillDebuggerTabName);
}

void FAISkillDebuggerModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FAISkillDebuggerCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FAISkillDebuggerCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAISkillDebuggerModule, AISkillDebugger)