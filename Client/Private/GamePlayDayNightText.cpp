#include "pch.h"
#include "GamePlayDayNightText.h"

#include "World.h"
#include "GameManager.h"

HRESULT Client::CGamePlayDayNightText::PreInitialize()
{
	m_wpGameManager = CGameManager::GetInstance();

	SetTextPosition({ 625.0f, 16.0f });
	SetTextScale(0.3f);
	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	return CText::PreInitialize();
}

HRESULT Client::CGamePlayDayNightText::Initialize()
{
	return S_OK;
}

HRESULT Client::CGamePlayDayNightText::PostInitialize()
{
	return S_OK;
}

HRESULT Client::CGamePlayDayNightText::BeginPlay()
{
	return S_OK;
}

int32 Client::CGamePlayDayNightText::PreTick(float _fDeltaSeconds)
{
	switch (CText::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CGamePlayDayNightText::Tick(float _fDeltaSeconds)
{
	switch (CText::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	wstring wstrTime = L"";
	EDayType eDayType = m_wpGameManager.lock()->GetDayType();

	switch (eDayType)
	{
	case EDayType::DAY:
	{
		int32 iNumDay = m_wpGameManager.lock()->GetSumDay();
		wstrTime = to_wstring(iNumDay) + L"ÀÏÂ÷ ³·";
	}
	break;

	case EDayType::NIGHT:
	{
		int32 iNumNight = m_wpGameManager.lock()->GetSumNight();
		wstrTime = to_wstring(iNumNight) + L"ÀÏÂ÷ ¹ã";
	}
	break;
	}

	SetText(wstrTime);
	return 0;
}

int32 Client::CGamePlayDayNightText::PostTick(float _fDeltaSeconds)
{
	switch (CText::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CGamePlayDayNightText::EndPlay()
{
	if (FAILED(CText::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CGamePlayDayNightText::Render()
{
	CText::Render();
}

void Client::CGamePlayDayNightText::Release()
{
	CText::Release();
}
