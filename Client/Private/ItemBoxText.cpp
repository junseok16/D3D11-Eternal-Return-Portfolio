#include "pch.h"
#include "ItemBoxText.h"

#include "World.h"
#include "GameManager.h"
#include "Survivor.h"

HRESULT Client::CItemBoxText::PreInitialize()
{
	m_wpGameManager = CGameManager::GetInstance();

	SetTextPosition({ 775.0f, 282.0f });
	SetTextScale(0.45f);
	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	return CText::PreInitialize();
}

HRESULT Client::CItemBoxText::Initialize()
{
	return CText::Initialize();
}

HRESULT Client::CItemBoxText::PostInitialize()
{
	return CText::PostInitialize();
}

HRESULT Client::CItemBoxText::BeginPlay()
{
	return CText::BeginPlay();
}

int32 Client::CItemBoxText::PreTick(float _fDeltaSeconds)
{
	switch (CText::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CItemBoxText::Tick(float _fDeltaSeconds)
{
	switch (CText::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	if (m_wpGameManager.lock()->GetSurvivor()->IsBoxOpened())
	{
		SetText(L"»óÀÚ");
	}
	else
	{
		SetText(L"");
	}
	
	return 0;
}

int32 Client::CItemBoxText::PostTick(float _fDeltaSeconds)
{
	switch (CText::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CItemBoxText::EndPlay()
{
	if (FAILED(CText::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CItemBoxText::Render()
{
	CText::Render();
}

void Client::CItemBoxText::Release()
{
	CText::Release();
}
