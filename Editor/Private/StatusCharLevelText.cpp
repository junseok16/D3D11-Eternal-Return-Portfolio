#include "pch.h"
#include "StatusCharLevelText.h"

#include "GameManager.h"
#include "Survivor.h"

HRESULT Editor::CStatusCharLevelText::PreInitialize()
{
	m_wpGameManager = CGameManager::GetInstance();
	m_wpSurvivor = m_wpGameManager.lock()->GetSurvivor();

	SetTextPosition({ 223.0f, 702.0f });
	SetTextScale(0.4f);
	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	return CText::PreInitialize();
}

HRESULT Editor::CStatusCharLevelText::Initialize()
{
	return S_OK;
}

HRESULT Editor::CStatusCharLevelText::PostInitialize()
{
	return S_OK;
}

HRESULT Editor::CStatusCharLevelText::BeginPlay()
{
	return S_OK;
}

int32 Editor::CStatusCharLevelText::PreTick(float _fDeltaSeconds)
{
	switch (CText::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CStatusCharLevelText::Tick(float _fDeltaSeconds)
{
	switch (CText::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	int32 iCurLevel = m_wpGameManager.lock()->GetSurvivor()->GetCurLevel() + 1;
	SetText(to_wstring(iCurLevel));
	return 0;
}

int32 Editor::CStatusCharLevelText::PostTick(float _fDeltaSeconds)
{
	switch (CText::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CStatusCharLevelText::EndPlay()
{
	if (FAILED(CText::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CStatusCharLevelText::Render()
{
	CText::Render();
}

void Editor::CStatusCharLevelText::Release()
{
	CText::Release();
}
