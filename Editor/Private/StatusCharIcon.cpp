#include "pch.h"
#include "StatusCharIcon.h"

HRESULT Editor::CStatusCharIcon::PreInitialize()
{
	SetActorRenderType(ERenderType::TRANSLUCENT_OBJECT);
	SetPrimitiveType(EPrimitiveType::POINT);

	switch (m_eCharacterStatusType)
	{
	case Editor::ECharacterStatusType::ATTACK_POWER:						SetImageNames({ L"Ico_ChaStat_AttackPower" });						break;
	case Editor::ECharacterStatusType::DEFENSE:								SetImageNames({ L"Ico_ChaStat_Defense" });							break;
	case Editor::ECharacterStatusType::INCREASE_BASIC_ATTACK_DAMAGE_RATIO:	SetImageNames({ L"Ico_ChaStat_IncreaseBasicAttackDamageRatio" });	break;
	case Editor::ECharacterStatusType::NORMAL_ATTACK_DAMAGE_REDUCTION:		SetImageNames({ L"Ico_ChaStat_NormalAttack_DamageReduction" });		break;
	case Editor::ECharacterStatusType::SKILL_AMP_RATIO:						SetImageNames({ L"Ico_ChaStat_SkillAmpRatio" });					break;
	case Editor::ECharacterStatusType::SKILL_DAMAGE_REDUCTION:				SetImageNames({ L"Ico_ChaStat_SkillDamageReduction" });				break;
	case Editor::ECharacterStatusType::ATTACK_SPEED_RATIO:					SetImageNames({ L"Ico_ChaStat_AttackSpeedRatio" });					break;
	case Editor::ECharacterStatusType::MOVE_SPEED_RATIO:					SetImageNames({ L"Ico_ChaStat_MoveSpeedRatio" });					break;
	default:																CHECKF(false, L"Character status type is not designated.");			break;
	}

	return CImage::PreInitialize();
}

HRESULT Editor::CStatusCharIcon::Initialize()
{
	SetWidth(15.0f);
	SetHeight(14.0f);

	switch (m_eCharacterStatusType)
	{
	case Editor::ECharacterStatusType::ATTACK_POWER:						SetPivot({ 124.0f, 642.0f });	break;
	case Editor::ECharacterStatusType::DEFENSE:								SetPivot({ 180.0f, 642.0f });	break;
	case Editor::ECharacterStatusType::INCREASE_BASIC_ATTACK_DAMAGE_RATIO:	SetPivot({ 124.0f, 662.0f });	break;
	case Editor::ECharacterStatusType::NORMAL_ATTACK_DAMAGE_REDUCTION:		SetPivot({ 180.0f, 662.0f });	break;
	case Editor::ECharacterStatusType::SKILL_AMP_RATIO:						SetPivot({ 124.0f, 682.0f });	break;
	case Editor::ECharacterStatusType::SKILL_DAMAGE_REDUCTION:				SetPivot({ 180.0f, 682.0f });	break;
	case Editor::ECharacterStatusType::ATTACK_SPEED_RATIO:					SetPivot({ 124.0f, 702.0f });	break;
	case Editor::ECharacterStatusType::MOVE_SPEED_RATIO:					SetPivot({ 180.0f, 702.0f });	break;
	default: CHECKF(false, L"Character status type is not designated.");									break;
	}

	return CImage::Initialize();
}

HRESULT Editor::CStatusCharIcon::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CStatusCharIcon::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CStatusCharIcon::PreTick(float _fDeltaSeconds)
{
	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CStatusCharIcon::Tick(float _fDeltaSeconds)
{
	switch (CImage::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CStatusCharIcon::PostTick(float _fDeltaSeconds)
{
	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CStatusCharIcon::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CStatusCharIcon::Render()
{
	CImage::Render();
}

void Editor::CStatusCharIcon::Release()
{
	CImage::Release();
}
