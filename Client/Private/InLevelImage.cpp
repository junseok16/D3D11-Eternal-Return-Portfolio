#include "pch.h"
#include "InLevelImage.h"

HRESULT Client::CInLevelImage::PreInitialize()
{
	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	SetPrimitiveType(EPrimitiveType::POINT);

	SetImageNames({ L"Img_ChaLevel_Bg" });

	return CImage::PreInitialize();
}

HRESULT Client::CInLevelImage::Initialize()
{
	// SetPivot({ todo });
	SetWidth(85.0f);
	SetHeight(15.0f);
	return CImage::Initialize();
}

HRESULT Client::CInLevelImage::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CInLevelImage::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CInLevelImage::PreTick(float _fDeltaSeconds)
{
	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CInLevelImage::Tick(float _fDeltaSeconds)
{
	switch (CImage::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CInLevelImage::PostTick(float _fDeltaSeconds)
{
	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CInLevelImage::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CInLevelImage::Render()
{
	CImage::Render();
}

void Client::CInLevelImage::Release()
{
	CImage::Release();
}
