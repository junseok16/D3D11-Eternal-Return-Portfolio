#include "pch.h"
#include "GamePlayTimeText.h"

#include "World.h"
#include "GameManager.h"

HRESULT Editor::CGamePlayTimeText::PreInitialize()
{
	m_wpGameManager = CGameManager::GetInstance();

	SetTextPosition({ 602.0f, 36.0f });
	SetTextScale(0.6f);
	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	return CText::PreInitialize();
}

HRESULT Editor::CGamePlayTimeText::Initialize()
{
	return S_OK;
}

HRESULT Editor::CGamePlayTimeText::PostInitialize()
{
	return S_OK;
}

HRESULT Editor::CGamePlayTimeText::BeginPlay()
{
	return S_OK;
}

int32 Editor::CGamePlayTimeText::PreTick(float _fDeltaSeconds)
{
	switch (CText::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CGamePlayTimeText::Tick(float _fDeltaSeconds)
{
	switch (CText::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	switch (m_wpGameManager.lock()->GetDayType())
	{
	case EDayType::DAY:
		m_fLeftSeconds = m_wpGameManager.lock()->GetDayTime();
		break;

	case EDayType::NIGHT:
		m_fLeftSeconds = m_wpGameManager.lock()->GetNightTime();
		break;
	}

	int32 iLeftTime = static_cast<int32>(m_fLeftSeconds);

	int32 iMinutes = iLeftTime / 60;
	int32 iSeconds = iLeftTime % 60;


	wstring wstrTime = format(L"{0:02}:{1:02} {2:03}", iMinutes, iSeconds, (int32)(1.0f / _fDeltaSeconds));
	SetText(wstrTime);
	return 0;
}

int32 Editor::CGamePlayTimeText::PostTick(float _fDeltaSeconds)
{
	switch (CText::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CGamePlayTimeText::EndPlay()
{
	if (FAILED(CText::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CGamePlayTimeText::Render()
{
	CText::Render();
}

void Editor::CGamePlayTimeText::Release()
{
	CText::Release();
}
