// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class UFMSkillBase;
class AFMAICharacter;
/**
 * 
 */
class AISKILLDEBUGGER_API SAISkillDebuggerMenu : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SAISkillDebuggerMenu)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

// Run Behavior
public:
	void OnRunBehaviorCheckboxStateChanged(ECheckBoxState NewState);
	ECheckBoxState IsRunBehaviorBoxChecked() const;

protected:
	bool bIsRunBehaviorBoxChecked = false;

// Character List
public:
	void GetAIsInLevel();
	TSharedRef<SWidget> GenerateAIComboItem(TWeakObjectPtr<AFMAICharacter> InAI);
	void OnAISelected(TWeakObjectPtr<AFMAICharacter> NewSelection, ESelectInfo::Type SelectInfo);
	FText GetSelectedAIText() const;

protected:
	TArray<TWeakObjectPtr<AFMAICharacter>> AIs;
	TWeakObjectPtr<AFMAICharacter> SelectedAI;

// Skill List
public:
	void GetAISkills();
	TSharedRef<SWidget> GenerateAISkillComboItem(TWeakObjectPtr<UFMSkillBase> InAISkill);
	void OnAISkillSelected(TWeakObjectPtr<UFMSkillBase> NewSelection, ESelectInfo::Type SelectInfo);
	FText GetSelectedAISkillText() const;

protected:
	TArray<TWeakObjectPtr<UFMSkillBase>> AISkills;
	TWeakObjectPtr<UFMSkillBase> SelectedAISkill;

// Activate Skill
public:
	FReply OnActivateSkillButtonClicked();
	
};
