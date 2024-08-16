#include "pch.h"
#include "GamePlayBackground.h"

HRESULT Client::CGamePlayBackground::PreInitialize()
{
	SetActorRenderType(ERenderType::TRANSLUCENT_OBJECT);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetImageNames({ L"Img_HUDBg_02", L"Img_HUDBg_03", L"Img_HUDBg_04" });
	return CImage::PreInitialize();
}

HRESULT Client::CGamePlayBackground::Initialize()
{
	SetPivot({ 408.0f, 0.0f });
	SetWidth(464.0f);
	SetHeight(80.0f);
	return CImage::Initialize();
}

HRESULT Client::CGamePlayBackground::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CGamePlayBackground::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CGamePlayBackground::PreTick(float _fDeltaSeconds)
{
	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CGamePlayBackground::Tick(float _fDeltaSeconds)
{
	switch (CImage::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CGamePlayBackground::PostTick(float _fDeltaSeconds)
{
	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CGamePlayBackground::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CGamePlayBackground::Render()
{
	CImage::Render();
}

void Client::CGamePlayBackground::Release()
{
	CImage::Release();
}
