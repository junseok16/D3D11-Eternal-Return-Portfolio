#include "pch.h"
#include "ItemInfoBackground.h"

HRESULT Client::CItemInfoBackground::PreInitialize()
{
	SetActorRenderType(ERenderType::TRANSLUCENT_OBJECT);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetImageNames({ L"Img_Popup_Panel" });
	return CImage::PreInitialize();
}

HRESULT Client::CItemInfoBackground::Initialize()
{
	SetPivot({ 766.0f, 418.0f });
	SetWidth(256.0f);
	SetHeight(174.0f);
	return CImage::Initialize();
}

HRESULT Client::CItemInfoBackground::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CItemInfoBackground::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CItemInfoBackground::PreTick(float _fDeltaSeconds)
{
	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CItemInfoBackground::Tick(float _fDeltaSeconds)
{
	switch (CImage::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CItemInfoBackground::PostTick(float _fDeltaSeconds)
{
	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CItemInfoBackground::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CItemInfoBackground::Render()
{
	CImage::Render();
}

void Client::CItemInfoBackground::Release()
{
	CImage::Release();
}
