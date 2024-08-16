#include "pch.h"
#include "SkillUpgradeButton.h"

#include "GameManager.h"
#include "Survivor.h"

HRESULT Editor::CSkillUpgradeButton::PreInitialize()
{
	m_wpGameManager = CGameManager::GetInstance();
	m_wpSurvivor = m_wpGameManager.lock()->GetSurvivor();

	// shared_ptr<CLevel> spLevel = CWorld::GetInstance()->GetCurLevel();
	// m_wpSurvivor = static_pointer_cast<CSurvivor>(spLevel->GetController()->GetPawn());

	// 델리게이트를 추가합니다.
	AddOnButtonUpInDelegate(static_pointer_cast<CSkillUpgradeButton>(shared_from_this()), &CSkillUpgradeButton::OnButtonUpIn);
	AddOnButtonUpOutDelegate(static_pointer_cast<CSkillUpgradeButton>(shared_from_this()), &CSkillUpgradeButton::OnButtonUpOut);

	SetActorRenderType(ERenderType::TRANSLUCENT_OBJECT);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetButtonNames
	(
		{ L"Btn_LevelUp_Disabled", L"Btn_LevelUp_Basic", L"Btn_LevelUp_MouseOver" }
	);
	return CButton::PreInitialize();
}

HRESULT Editor::CSkillUpgradeButton::Initialize()
{
	SetWidth(32.0f);
	SetHeight(37.0f);

	switch (m_eSkillType)
	{
	case Editor::ESkillType::FIRST:		SetPivot({ 468.0f, 602.0f });	break;
	case Editor::ESkillType::SECOND:	SetPivot({ 518.0f, 602.0f });	break;
	case Editor::ESkillType::THIRD:		SetPivot({ 568.0f, 602.0f });	break;
	case Editor::ESkillType::FOURTH:	SetPivot({ 618.0f, 602.0f });	break;
	case Editor::ESkillType::PASSIVE:	SetPivot({ 668.0f, 602.0f });	break;
	default: CHECKF(false, L"Skill type is not designated.");			break;
	}

	return CButton::Initialize();
}

HRESULT Editor::CSkillUpgradeButton::PostInitialize()
{
	if (FAILED(CButton::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CSkillUpgradeButton::BeginPlay()
{
	if (FAILED(CButton::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CSkillUpgradeButton::PreTick(float _fDeltaSeconds)
{
	switch (CButton::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	// 스킬 포인트가 있는 경우
	if (0 < m_wpGameManager.lock()->GetSurvivor()->GetCurSkillPoint())
	{
		int32 iCurSkillLevel = m_wpGameManager.lock()->GetSurvivor()->GetCurSkillLevel(m_eSkillType);
		int32 iMaxSkillLevel = m_wpGameManager.lock()->GetSurvivor()->GetMaxSkillLevel(m_eSkillType);

		// 스킬을 올릴 수 있는 경우
		if (iCurSkillLevel <= iMaxSkillLevel)
		{
			m_eButtonState = EButtonState::ENABLE;
		}
		else
		{
			m_eButtonState = EButtonState::DISABLE;
		}
	}
	// 스킬 포인트가 없는 경우
	else
	{
		m_eButtonState = EButtonState::INACTIVE;
	}

	return 0;
}

int32 Editor::CSkillUpgradeButton::Tick(float _fDeltaSeconds)
{
	switch (CButton::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	switch (m_eButtonState)
	{
	case Engine::EButtonState::INACTIVE:
		break;

	case Engine::EButtonState::ENABLE:
	{
		switch (m_eButtonMouseState)
		{
		case Engine::EButtonMouseState::RELEASE:	SetTextureIndex(1);	break;
		case Engine::EButtonMouseState::HOVER:		SetTextureIndex(2); break;
		case Engine::EButtonMouseState::PRESS_IN:	SetTextureIndex(2); break;
		case Engine::EButtonMouseState::PRESS_OUT:	SetTextureIndex(1); break;
		case Engine::EButtonMouseState::DOWN:		SetTextureIndex(2); break;
		case Engine::EButtonMouseState::UP_OUT:		SetTextureIndex(1); break;
		case Engine::EButtonMouseState::UP_IN:							break;
		default:														break;
		}
	}
	break;

	case Engine::EButtonState::DISABLE:
		SetTextureIndex(0);
		break;

	default:
		break;
	}
	return 0;
}

int32 Editor::CSkillUpgradeButton::PostTick(float _fDeltaSeconds)
{
	switch (CButton::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CSkillUpgradeButton::EndPlay()
{
	if (FAILED(CButton::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CSkillUpgradeButton::Render()
{
	CButton::Render();
}

void Editor::CSkillUpgradeButton::Release()
{
	CButton::Release();
}

void Editor::CSkillUpgradeButton::OnButtonUpIn()
{
	m_wpGameManager.lock()->GetSurvivor()->AddSkillLevel(m_eSkillType, 1);
	m_wpGameManager.lock()->GetSurvivor()->AddSkillPoint(-1);
	SetTextureIndex(1);
}

void Editor::CSkillUpgradeButton::OnButtonUpOut()
{
}
