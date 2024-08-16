#include "pch.h"
#include "CraftImage.h"

HRESULT Client::CCraftImage::PreInitialize()
{
	SetActorRenderType(ERenderType::TRANSLUCENT_USER_INTERFACE);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetImageNames({ L"Ico_Crafting" });
	return CImage::PreInitialize();
}

HRESULT Client::CCraftImage::Initialize()
{
	SetWidth(26.0f);
	SetHeight(26.0f);
	SetPivot({ 784.0f, 608.0f });
	return CImage::Initialize();
}

HRESULT Client::CCraftImage::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CCraftImage::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	SetTextureIndex(0);
	return S_OK;
}

int32 Client::CCraftImage::PreTick(float _fDeltaSeconds)
{
	if (!m_bActive) { return 0; }

	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CCraftImage::Tick(float _fDeltaSeconds)
{
	if (!m_bActive) { return 0; }

	switch (CImage::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CCraftImage::PostTick(float _fDeltaSeconds)
{
	if (!m_bActive) { return 0; }

	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CCraftImage::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CCraftImage::Render()
{
	if (!m_bActive) { return; }

	CImage::Render();
}

void Client::CCraftImage::Release()
{
	CImage::Release();
}
