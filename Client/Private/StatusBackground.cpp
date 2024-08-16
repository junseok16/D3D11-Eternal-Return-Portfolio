#include "pch.h"
#include "StatusBackground.h"

HRESULT Client::CStatusBackground::PreInitialize()
{
	SetActorRenderType(ERenderType::TRANSLUCENT_OBJECT);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetImageNames({ L"Img_MainBg_06" });
	return CImage::PreInitialize();
}

HRESULT Client::CStatusBackground::Initialize()
{
	SetPivot({ 118.0f, 638.0f });
	SetWidth(333.0f);
	SetHeight(82.0f);
	return CImage::Initialize();
}

HRESULT Client::CStatusBackground::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CStatusBackground::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CStatusBackground::PreTick(float _fDeltaSeconds)
{
	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CStatusBackground::Tick(float _fDeltaSeconds)
{
	switch (CImage::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CStatusBackground::PostTick(float _fDeltaSeconds)
{
	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CStatusBackground::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CStatusBackground::Render()
{
	CImage::Render();
}

void Client::CStatusBackground::Release()
{
	CImage::Release();
}
