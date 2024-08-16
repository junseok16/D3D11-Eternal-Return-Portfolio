#include "pch.h"
#include "ItemBoxBackground.h"

HRESULT Client::CItemBoxBackground::PreInitialize()
{
	SetActorRenderType(ERenderType::TRANSLUCENT_OBJECT);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetImageNames({ L"Img_Popup_Panel" });
	return CImage::PreInitialize();
}

HRESULT Client::CItemBoxBackground::Initialize()
{
	SetPivot({ 766.0f, 276.0f });
	SetWidth(220.0f);
	SetHeight(126.0f);
	return CImage::Initialize();
}

HRESULT Client::CItemBoxBackground::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CItemBoxBackground::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CItemBoxBackground::PreTick(float _fDeltaSeconds)
{
	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CItemBoxBackground::Tick(float _fDeltaSeconds)
{
	switch (CImage::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CItemBoxBackground::PostTick(float _fDeltaSeconds)
{
	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CItemBoxBackground::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CItemBoxBackground::Render()
{
	CImage::Render();
}

void Client::CItemBoxBackground::Release()
{
	CImage::Release();
}
