#include "pch.h"
#include "GamePlayTimeText.h"

#include "World.h"
#include "GameManager.h"

HRESULT Client::CGamePlayTimeText::PreInitialize()
{
	m_wpGameManager = CGameManager::GetInstance();

	SetTextPosition({ 602.0f, 36.0f });
	SetTextScale(0.6f);
	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	return CText::PreInitialize();
}

HRESULT Client::CGamePlayTimeText::Initialize()
{
	return S_OK;
}

HRESULT Client::CGamePlayTimeText::PostInitialize()
{
	return S_OK;
}

HRESULT Client::CGamePlayTimeText::BeginPlay()
{
	return S_OK;
}

int32 Client::CGamePlayTimeText::PreTick(float _fDeltaSeconds)
{
	switch (CText::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CGamePlayTimeText::Tick(float _fDeltaSeconds)
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


	wstring wstrTime = format(L"{0:02}:{1:02}", iMinutes, iSeconds);
	SetText(wstrTime);
	return 0;
}

int32 Client::CGamePlayTimeText::PostTick(float _fDeltaSeconds)
{
	switch (CText::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CGamePlayTimeText::EndPlay()
{
	if (FAILED(CText::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CGamePlayTimeText::Render()
{
	CText::Render();
}

void Client::CGamePlayTimeText::Release()
{
	CText::Release();
}
