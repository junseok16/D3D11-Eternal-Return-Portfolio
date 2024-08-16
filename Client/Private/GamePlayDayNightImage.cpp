#include "pch.h"
#include "GamePlayDayNightImage.h"

#include "World.h"
#include "GameManager.h"

HRESULT Client::CGamePlayDayNightImage::PreInitialize()
{
	m_wpGameManager = CGameManager::GetInstance();

	SetActorRenderType(ERenderType::TRANSLUCENT_USER_INTERFACE);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetImageNames({ L"Ico_DaySun", L"Ico_NightMoon" });
	return CImage::PreInitialize();
}

HRESULT Client::CGamePlayDayNightImage::Initialize()
{
	SetWidth(20.0f);
	SetHeight(20.0f);
	SetPivot({ 603.0f, 16.0f });
	return CImage::Initialize();
}

HRESULT Client::CGamePlayDayNightImage::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CGamePlayDayNightImage::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CGamePlayDayNightImage::PreTick(float _fDeltaSeconds)
{
	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CGamePlayDayNightImage::Tick(float _fDeltaSeconds)
{
	switch (CImage::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	EDayType eDayType = m_wpGameManager.lock()->GetDayType();
	switch (eDayType)
	{
	case EDayType::DAY:		SetTextureIndex(0); break;
	case EDayType::NIGHT:	SetTextureIndex(1);	break;
	}

	return 0;
}

int32 Client::CGamePlayDayNightImage::PostTick(float _fDeltaSeconds)
{
	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CGamePlayDayNightImage::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CGamePlayDayNightImage::Render()
{
	CImage::Render();
}

void Client::CGamePlayDayNightImage::Release()
{
	CImage::Release();
}
