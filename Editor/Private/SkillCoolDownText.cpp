#include "pch.h"
#include "SkillCoolDownText.h"

#include "GameManager.h"
#include "Survivor.h"

HRESULT Editor::CSkillCoolDownText::PreInitialize()
{
	m_wpGameManager = CGameManager::GetInstance();
	m_wpSurvivor = m_wpGameManager.lock()->GetSurvivor();

	// shared_ptr<CLevel> spLevel = CWorld::GetInstance()->GetCurLevel();
	// m_wpSurvivor = static_pointer_cast<CSurvivor>(spLevel->GetController()->GetPawn());

	switch (m_eSkillType)
	{
	case Editor::ESkillType::FIRST:
		SetTextPosition({ 461.0f, 665.0f });
		break;

	case Editor::ESkillType::SECOND:
		SetTextPosition({ 511.0f, 665.0f });
		break;

	case Editor::ESkillType::THIRD:
		SetTextPosition({ 561.0f, 665.0f });
		break;

	case Editor::ESkillType::FOURTH:
		SetTextPosition({ 611.0f, 665.0f });
		break;

	default:
		break;
	}

	SetTextScale(0.5f);
	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	return CText::PreInitialize();
}

HRESULT Editor::CSkillCoolDownText::Initialize()
{
	return S_OK;
}

HRESULT Editor::CSkillCoolDownText::PostInitialize()
{
	return S_OK;
}

HRESULT Editor::CSkillCoolDownText::BeginPlay()
{
	return S_OK;
}

int32 Editor::CSkillCoolDownText::PreTick(float _fDeltaSeconds)
{
	switch (CText::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CSkillCoolDownText::Tick(float _fDeltaSeconds)
{
	switch (CText::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	int32 iCoolDown = static_cast<int32>(m_wpGameManager.lock()->GetSurvivor()->GetCurCoolDown(m_eSkillType));
	SetText(to_wstring(iCoolDown));
	return 0;
}

int32 Editor::CSkillCoolDownText::PostTick(float _fDeltaSeconds)
{
	switch (CText::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CSkillCoolDownText::EndPlay()
{
	if (FAILED(CText::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CSkillCoolDownText::Render()
{
	CText::Render();
}

void Editor::CSkillCoolDownText::Release()
{
	CText::Render();
}
