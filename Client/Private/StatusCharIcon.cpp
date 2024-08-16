#include "pch.h"
#include "StatusCharIcon.h"

HRESULT Client::CStatusCharIcon::PreInitialize()
{
	SetActorRenderType(ERenderType::TRANSLUCENT_OBJECT);
	SetPrimitiveType(EPrimitiveType::POINT);

	switch (m_eCharacterStatusType)
	{
	case Client::ECharacterStatusType::ATTACK_POWER:						SetImageNames({ L"Ico_ChaStat_AttackPower" });						break;
	case Client::ECharacterStatusType::DEFENSE:								SetImageNames({ L"Ico_ChaStat_Defense" });							break;
	case Client::ECharacterStatusType::INCREASE_BASIC_ATTACK_DAMAGE_RATIO:	SetImageNames({ L"Ico_ChaStat_IncreaseBasicAttackDamageRatio" });	break;
	case Client::ECharacterStatusType::NORMAL_ATTACK_DAMAGE_REDUCTION:		SetImageNames({ L"Ico_ChaStat_NormalAttack_DamageReduction" });		break;
	case Client::ECharacterStatusType::SKILL_AMP_RATIO:						SetImageNames({ L"Ico_ChaStat_SkillAmpRatio" });					break;
	case Client::ECharacterStatusType::SKILL_DAMAGE_REDUCTION:				SetImageNames({ L"Ico_ChaStat_SkillDamageReduction" });				break;
	case Client::ECharacterStatusType::ATTACK_SPEED_RATIO:					SetImageNames({ L"Ico_ChaStat_AttackSpeedRatio" });					break;
	case Client::ECharacterStatusType::MOVE_SPEED_RATIO:					SetImageNames({ L"Ico_ChaStat_MoveSpeedRatio" });					break;
	default:																CHECKF(false, L"Character status type is not designated.");			break;
	}

	return CImage::PreInitialize();
}

HRESULT Client::CStatusCharIcon::Initialize()
{
	SetWidth(15.0f);
	SetHeight(14.0f);

	switch (m_eCharacterStatusType)
	{
	case Client::ECharacterStatusType::ATTACK_POWER:						SetPivot({ 124.0f, 642.0f });	break;
	case Client::ECharacterStatusType::DEFENSE:								SetPivot({ 180.0f, 642.0f });	break;
	case Client::ECharacterStatusType::INCREASE_BASIC_ATTACK_DAMAGE_RATIO:	SetPivot({ 124.0f, 662.0f });	break;
	case Client::ECharacterStatusType::NORMAL_ATTACK_DAMAGE_REDUCTION:		SetPivot({ 180.0f, 662.0f });	break;
	case Client::ECharacterStatusType::SKILL_AMP_RATIO:						SetPivot({ 124.0f, 682.0f });	break;
	case Client::ECharacterStatusType::SKILL_DAMAGE_REDUCTION:				SetPivot({ 180.0f, 682.0f });	break;
	case Client::ECharacterStatusType::ATTACK_SPEED_RATIO:					SetPivot({ 124.0f, 702.0f });	break;
	case Client::ECharacterStatusType::MOVE_SPEED_RATIO:					SetPivot({ 180.0f, 702.0f });	break;
	default: CHECKF(false, L"Character status type is not designated.");									break;
	}

	return CImage::Initialize();
}

HRESULT Client::CStatusCharIcon::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CStatusCharIcon::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CStatusCharIcon::PreTick(float _fDeltaSeconds)
{
	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CStatusCharIcon::Tick(float _fDeltaSeconds)
{
	switch (CImage::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CStatusCharIcon::PostTick(float _fDeltaSeconds)
{
	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CStatusCharIcon::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CStatusCharIcon::Render()
{
	CImage::Render();
}

void Client::CStatusCharIcon::Release()
{
	CImage::Release();
}
