#include "pch.h"
#include "SkillImage.h"

#include "GameManager.h"
#include "Survivor.h"

HRESULT Editor::CSkillImage::PreInitialize()
{
	m_wpGameManager = CGameManager::GetInstance();

	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	SetPrimitiveType(EPrimitiveType::POINT);

	switch (m_eSkillType)
	{
	case Editor::ESkillType::FIRST:		SetImageNames({ L"SkillIcon_1007200", L"SkillIcon_1002200" });	break;
	case Editor::ESkillType::SECOND:	SetImageNames({ L"SkillIcon_1007300", L"SkillIcon_1002300" });	break;
	case Editor::ESkillType::THIRD:		SetImageNames({ L"SkillIcon_1007400", L"SkillIcon_1002400" });	break;
	case Editor::ESkillType::FOURTH:	SetImageNames({ L"SkillIcon_1007500", L"SkillIcon_1002500" });	break;
	case Editor::ESkillType::PASSIVE:	SetImageNames({ L"SkillIcon_1007100", L"SkillIcon_1002100" });	break;
	default: CHECKF(false, L"Skill type is not designated.");											break;
	}
	/*
	switch (m_eSurvivorType)
	{
	case Editor::ESurvivorType::HYUNWOO:
	{
		switch (m_eSkillType)
		{
		case Editor::ESkillType::FIRST:		SetImageNames({ L"SkillIcon_1007200", L"SkillIcon_1002200" });	break;
		case Editor::ESkillType::SECOND:	SetImageNames({ L"SkillIcon_1007300", L"SkillIcon_1002300" });	break;
		case Editor::ESkillType::THIRD:		SetImageNames({ L"SkillIcon_1007400", L"SkillIcon_1002400" });	break;
		case Editor::ESkillType::FOURTH:	SetImageNames({ L"SkillIcon_1007500", L"SkillIcon_1002500" });	break;
		case Editor::ESkillType::PASSIVE:	SetImageNames({ L"SkillIcon_1007100", L"SkillIcon_1002100" });	break;
		default: CHECKF(false, L"Skill type is not designated.");						 break;
		}
	}
	break;

	case Editor::ESurvivorType::AYA:
	{
		switch (m_eSkillType)
		{
		case Editor::ESkillType::FIRST:		SetImageNames({ L"SkillIcon_1002200" });	break;
		case Editor::ESkillType::SECOND:	SetImageNames({ L"SkillIcon_1002300" });	break;
		case Editor::ESkillType::THIRD:		SetImageNames({ L"SkillIcon_1002400" });	break;
		case Editor::ESkillType::FOURTH:	SetImageNames({ L"SkillIcon_1002500" });	break;
		case Editor::ESkillType::PASSIVE:	SetImageNames({ L"SkillIcon_1002100" });	break;
		default: CHECKF(false, L"Skill type is not designated.");						break;
		}
	}
	break;

	case Editor::ESurvivorType::YUKI:
	{
		switch (m_eSkillType)
		{
		case Editor::ESkillType::FIRST:		SetImageNames({ L"SkillIcon_1011200" });	break;
		case Editor::ESkillType::SECOND:	SetImageNames({ L"SkillIcon_1011300" });	break;
		case Editor::ESkillType::THIRD:		SetImageNames({ L"SkillIcon_1011400" });	break;
		case Editor::ESkillType::FOURTH:	SetImageNames({ L"SkillIcon_1011500" });	break;
		case Editor::ESkillType::PASSIVE:	SetImageNames({ L"SkillIcon_1011100" });	break;
		default: CHECKF(false, L"Skill type is not designated.");						break;
		}
	}
	break;

	case Editor::ESurvivorType::ROZZI:
	{
		switch (m_eSkillType)
		{
		case Editor::ESkillType::FIRST:		SetImageNames({ L"SkillIcon_1021200" });	break;
		case Editor::ESkillType::SECOND:	SetImageNames({ L"SkillIcon_1021300" });	break;
		case Editor::ESkillType::THIRD:		SetImageNames({ L"SkillIcon_1021400" });	break;
		case Editor::ESkillType::FOURTH:	SetImageNames({ L"SkillIcon_1021500" });	break;
		case Editor::ESkillType::PASSIVE:	SetImageNames({ L"SkillIcon_1021100" });	break;
		default: CHECKF(false, L"Skill type is not designated.");						break;
		}
	}
	break;

	default:
		CHECKF(false, L"Survivor type is not designated.")
		break;
	}
	*/
	return CImage::PreInitialize();
}

HRESULT Editor::CSkillImage::Initialize()
{
	switch (m_eSkillType)
	{
	case Editor::ESkillType::FIRST:
	{
		SetPivot({ 463.0f, 645.0f });
		SetWidth(41.0f);
		SetHeight(45.0f);
	}
	break;

	case Editor::ESkillType::SECOND:
	{
		SetPivot({ 513.0f, 645.0f });
		SetWidth(41.0f);
		SetHeight(45.0f);
	}
	break;

	case Editor::ESkillType::THIRD:
	{
		SetPivot({ 563.0f, 645.0f });
		SetWidth(41.0f);
		SetHeight(45.0f);
	}
	break;

	case Editor::ESkillType::FOURTH:
	{
		SetPivot({ 613.0f, 645.0f });
		SetWidth(41.0f);
		SetHeight(45.0f);
	}
	break;

	case Editor::ESkillType::PASSIVE:
	{
		SetPivot({ 663.0f, 645.0f });
		SetWidth(41.0f);
		SetHeight(45.0f);
	}
	break;

	default: CHECKF(false, L"Skill type is not designated.");	break;
	}

	return CImage::Initialize();
}

HRESULT Editor::CSkillImage::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CSkillImage::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CSkillImage::PreTick(float _fDeltaSeconds)
{
	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CSkillImage::Tick(float _fDeltaSeconds)
{
	switch (CImage::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	switch (m_wpGameManager.lock()->GetSurvivor()->GetSurvivorType())
	{
	case ESurvivorType::HYUNWOO:
		SetTextureIndex(0);
		break;

	case ESurvivorType::AYA:
		SetTextureIndex(1);
		break;

	default:
		break;
	}

	return 0;
}

int32 Editor::CSkillImage::PostTick(float _fDeltaSeconds)
{
	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CSkillImage::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CSkillImage::Render()
{
	CImage::Render();
}

void Editor::CSkillImage::Release()
{
	CImage::Release();
}
