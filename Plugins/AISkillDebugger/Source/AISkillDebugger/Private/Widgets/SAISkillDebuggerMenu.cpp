// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SAISkillDebuggerMenu.h"

#include "EngineUtils.h"
#include "SlateOptMacros.h"
#include "AI/FMAIDataAsset.h"
#include "Character/FMAICharacter.h"
#include "Skill/FMSkillBase.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SAISkillDebuggerMenu::Construct(const FArguments& InArgs)
{
	GetAIsInLevel();
	
	ChildSlot
	[		
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Top)
			.Padding(10, 10)
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("AI")))
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Left)
			.Padding(10, 5)
			[
				SNew(SComboBox<TWeakObjectPtr<AFMAICharacter>>)
				.OptionsSource(&AIs)
				.OnGenerateWidget(this, &SAISkillDebuggerMenu::GenerateAIComboItem)
				.OnSelectionChanged(this, &SAISkillDebuggerMenu::OnAISelected)
				[
					SNew(STextBlock)
					.Text(this, &SAISkillDebuggerMenu::GetSelectedAIText)
				]
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Top)
			.Padding(10, 5)
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("Run Behavior")))
			]
			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Top)
			.Padding(10, 5)
			[
				SNew(SCheckBox)
				.OnCheckStateChanged(this, &SAISkillDebuggerMenu::OnRunBehaviorCheckboxStateChanged)
				.IsChecked(this, &SAISkillDebuggerMenu::IsRunBehaviorBoxChecked)
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Top)
			.Padding(10, 5)
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("스킬 목록")))
			]
			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Top)
			.Padding(10, 5)
			[
				SNew(SComboBox<TWeakObjectPtr<UFMSkillBase>>)
				.OptionsSource(&AISkills)
				.OnGenerateWidget(this, &SAISkillDebuggerMenu::GenerateAISkillComboItem)
				.OnSelectionChanged(this, &SAISkillDebuggerMenu::OnAISkillSelected)
				[
					SNew(STextBlock)
					.Text(this, &SAISkillDebuggerMenu::GetSelectedAISkillText)
				]
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Center)
		.Padding(10, 5)
		[
			SNew(SButton)
			.Text(FText::FromString(TEXT("스킬 발동")))
			.OnClicked(this, &SAISkillDebuggerMenu::OnActivateSkillButtonClicked)
		]
	];
}

void SAISkillDebuggerMenu::OnRunBehaviorCheckboxStateChanged(ECheckBoxState NewState)
{
	bIsRunBehaviorBoxChecked = NewState == ECheckBoxState::Checked ? true : false;

	if (SelectedAI.IsValid())
	{
		if (bIsRunBehaviorBoxChecked)
		{
			SelectedAI.Get()->RunBehaviorTree();
		}
		else
		{
			SelectedAI.Get()->StopBehaviorTree();
		}
	}
}

ECheckBoxState SAISkillDebuggerMenu::IsRunBehaviorBoxChecked() const
{
	return bIsRunBehaviorBoxChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

void SAISkillDebuggerMenu::GetAIsInLevel()
{
	AIs.Empty();

	UWorld* World = GEditor->PlayWorld;
	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't Get Current World"))
		
		return;		
	}

	for (const auto AI : TActorRange<AFMAICharacter>(World))
	{
		AIs.Add(AI);
	}
}

TSharedRef<SWidget> SAISkillDebuggerMenu::GenerateAIComboItem(TWeakObjectPtr<AFMAICharacter> InAI)
{
	return SNew(STextBlock)
		.Text(InAI.IsValid() ? FText::FromString(FString::Printf(TEXT("%s"), *InAI->GetName())) : FText::FromString(TEXT("Invalid Character")));
}

void SAISkillDebuggerMenu::OnAISelected(TWeakObjectPtr<AFMAICharacter> NewSelection, ESelectInfo::Type SelectInfo)
{
	SelectedAI = NewSelection;

	GetAISkills();

	if (SelectedAI.IsValid())
	{
		bIsRunBehaviorBoxChecked = SelectedAI.Get()->IsBehaviorTreeRunning();
	}
}

FText SAISkillDebuggerMenu::GetSelectedAIText() const
{
	return SelectedAI.IsValid() ? FText::FromString(FString::Printf(TEXT("%s"), *SelectedAI->GetName())) : FText::FromString(TEXT("Selected Actor"));
}

void SAISkillDebuggerMenu::GetAISkills()
{
	AISkills.Empty();
	
	if (SelectedAI.IsValid())
	{
		for (const auto& AISkill : SelectedAI.Get()->GetAIData()->AISkills)
		{
			AISkills.Add(AISkill.SkillData);
		}
	}
}

TSharedRef<SWidget> SAISkillDebuggerMenu::GenerateAISkillComboItem(TWeakObjectPtr<UFMSkillBase> InAISkill)
{
	return SNew(STextBlock)
		.Text(InAISkill.IsValid() ? FText::FromName(InAISkill.Get()->SkillName): FText::FromString(TEXT("Invalid Skill")));
}

void SAISkillDebuggerMenu::OnAISkillSelected(TWeakObjectPtr<UFMSkillBase> NewSelection, ESelectInfo::Type SelectInfo)
{
	SelectedAISkill = NewSelection;
}

FText SAISkillDebuggerMenu::GetSelectedAISkillText() const
{
	return SelectedAISkill.IsValid() ? FText::FromName(SelectedAISkill.Get()->SkillName) : FText::FromString(TEXT("Selected Skill"));
}

FReply SAISkillDebuggerMenu::OnActivateSkillButtonClicked()
{	
	if (SelectedAI.IsValid() && SelectedAISkill.IsValid())
	{
		SelectedAI.Get()->AIDebugActivateSkill(SelectedAISkill.Get());
	}
	
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
