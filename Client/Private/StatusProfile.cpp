#include "pch.h"
#include "StatusProfile.h"

#include "GameManager.h"
#include "Survivor.h"

HRESULT Client::CStatusProfile::PreInitialize()
{
	m_wpGameManager = CGameManager::GetInstance();

	SetActorRenderType(ERenderType::TRANSLUCENT_OBJECT);
	SetPrimitiveType(EPrimitiveType::POINT);

	SetImageNames
	(
		{
			L"CharProfile_Hyunwoo_S001",
			L"CharProfile_Aya_S001",
			L"CharProfile_Yuki_S003",
			L"CharProfile_Rozzi_S001"
		}
	);

	return CImage::PreInitialize();
}

HRESULT Client::CStatusProfile::Initialize()
{
	SetPivot({ 228.0f, 612.0f });
	SetWidth(82.0f);
	SetHeight(102.0f);
	return CImage::Initialize();
}

HRESULT Client::CStatusProfile::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CStatusProfile::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CStatusProfile::PreTick(float _fDeltaSeconds)
{
	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CStatusProfile::Tick(float _fDeltaSeconds)
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

int32 Client::CStatusProfile::PostTick(float _fDeltaSeconds)
{
	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CStatusProfile::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CStatusProfile::Render()
{
	CImage::Render();
}

void Client::CStatusProfile::Release()
{
	CImage::Release();
}
