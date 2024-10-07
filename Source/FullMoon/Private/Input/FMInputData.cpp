// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/FMInputData.h"
#include "InputMappingContext.h"
#include "InputAction.h"

UFMMenuInputData::UFMMenuInputData()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>
		MenuInputMappingContextRef(TEXT("/Game/_FullMoon/Input/Mappings/IMC_Menu.IMC_Menu"));
	if (MenuInputMappingContextRef.Succeeded())
	{
		MenuInputMappingContext = MenuInputMappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		MenuActionRef(TEXT("/Game/_FullMoon/Input/Actions/Menu/IA_Menu.IA_Menu"));
	if (MenuActionRef.Succeeded())
	{
		MenuAction = MenuActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		SettingActionRef(TEXT("/Game/_FullMoon/Input/Actions/Menu/IA_Settings.IA_Settings"));
	if (SettingActionRef.Succeeded())
	{
		SettingAction = SettingActionRef.Object;
	}
}

UFMBaseFreeInputData::UFMBaseFreeInputData()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>
		BaseFreeInputMappingContextRef(TEXT("/Game/_FullMoon/Input/Mappings/IMC_Base_Free.IMC_Base_Free"));
	if (BaseFreeInputMappingContextRef.Succeeded())
	{
		BaseFreeInputMappingContext = BaseFreeInputMappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		FreeMoveActionRef(TEXT("/Game/_FullMoon/Input/Actions/Base/IA_FreeMove.IA_FreeMove"));
	if (FreeMoveActionRef.Succeeded())
	{
		FreeMoveAction = FreeMoveActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		FreeLookActionRef(TEXT("/Game/_FullMoon/Input/Actions/Base/IA_FreeLook.IA_FreeLook"));
	if (FreeLookActionRef.Succeeded())
	{
		FreeLookAction = FreeLookActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		JumpActionRef(TEXT("/Game/_FullMoon/Input/Actions/Base/IA_Jump.IA_Jump"));
	if (JumpActionRef.Succeeded())
	{
		JumpAction = JumpActionRef.Object;
	}
}

UFMCombatInputData::UFMCombatInputData()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>
		CombatInputMappingContextRef(TEXT("/Game/_FullMoon/Input/Mappings/IMC_Combat.IMC_Combat"));
	if (CombatInputMappingContextRef.Succeeded())
	{
		CombatInputMappingContext = CombatInputMappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		SprintActionRef(TEXT("/Game/_FullMoon/Input/Actions/Combat/IA_Sprint.IA_Sprint"));
	if (SprintActionRef.Succeeded())
	{
		SprintAction = SprintActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		DashActionRef(TEXT("/Game/_FullMoon/Input/Actions/Combat/IA_Dash.IA_Dash"));
	if (DashActionRef.Succeeded())
	{
		DashAction = DashActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		AttackActionRef(TEXT("/Game/_FullMoon/Input/Actions/Combat/IA_Attack.IA_Attack"));
	if (AttackActionRef.Succeeded())
	{
		AttackAction = AttackActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		SpecialSkillActionRef(TEXT("/Game/_FullMoon/Input/Actions/Combat/IA_SpecialSkill.IA_SpecialSkill"));
	if (SpecialSkillActionRef.Succeeded())
	{
		SpecialSkillAction = SpecialSkillActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		NormalSkillAction1Ref(TEXT("/Game/_FullMoon/Input/Actions/Combat/IA_NormalSkill1.IA_NormalSkill1"));
	if (NormalSkillAction1Ref.Succeeded())
	{
		NormalSkillAction1 = NormalSkillAction1Ref.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		NormalSkillAction2Ref(TEXT("/Game/_FullMoon/Input/Actions/Combat/IA_NormalSkill2.IA_NormalSkill2"));
	if (NormalSkillAction2Ref.Succeeded())
	{
		NormalSkillAction2 = NormalSkillAction2Ref.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		UltimateSkillActionRef(TEXT("/Game/_FullMoon/Input/Actions/Combat/IA_UltimateSkill.IA_UltimateSkill"));
	if (UltimateSkillActionRef.Succeeded())
	{
		UltimateSkillAction = UltimateSkillActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		LockActionRef(TEXT("/Game/_FullMoon/Input/Actions/Combat/IA_Lock.IA_Lock"));
	if (LockActionRef.Succeeded())
	{
		LockAction = LockActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		ResurrectActionRef(TEXT("/Game/_FullMoon/Input/Actions/Combat/IA_Resurrect.IA_Resurrect"));
	if (ResurrectActionRef.Succeeded())
	{
		ResurrectAction = ResurrectActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		NoEquipActionRef(TEXT("/Game/_FullMoon/Input/Actions/Combat/IA_NoEquip.IA_NoEquip"));
	if (NoEquipActionRef.Succeeded())
	{
		NoEquipAction = NoEquipActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		InteractActionRef(TEXT("/Game/_FullMoon/Input/Actions/Combat/IA_Interaction.IA_Interaction"));
	if (InteractActionRef.Succeeded())
	{
		InteractAction = InteractActionRef.Object;
	}
}
