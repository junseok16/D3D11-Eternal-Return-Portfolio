#include "pch.h"
#include "StatusCharLevelCircleImage.h"

HRESULT Client::CStatusCharLevelCircleImage::PreInitialize()
{
	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetImageNames({ L"Ico_Map_PointPin_01" });

	return CImage::PreInitialize();
}

HRESULT Client::CStatusCharLevelCircleImage::Initialize()
{
	SetPivot({ 230.0f, 700.0f });
	SetWidth(23.0f);
	SetHeight(23.0f);
	return CImage::Initialize();
}

HRESULT Client::CStatusCharLevelCircleImage::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CStatusCharLevelCircleImage::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CStatusCharLevelCircleImage::PreTick(float _fDeltaSeconds)
{
	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CStatusCharLevelCircleImage::Tick(float _fDeltaSeconds)
{
	switch (CImage::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CStatusCharLevelCircleImage::PostTick(float _fDeltaSeconds)
{
	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CStatusCharLevelCircleImage::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CStatusCharLevelCircleImage::Render()
{
	CImage::Render();
}

void Client::CStatusCharLevelCircleImage::Release()
{
	CImage::Release();
}
