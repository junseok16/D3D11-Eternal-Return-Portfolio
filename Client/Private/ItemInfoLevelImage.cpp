#include "pch.h"
#include "ItemInfoLevelImage.h"

HRESULT Client::CItemInfoLevelImage::PreInitialize()
{
	SetActorRenderType(ERenderType::TRANSLUCENT_OBJECT);
	SetPrimitiveType(EPrimitiveType::POINT);

	SetPixelShader(L"PS_Color");
	SetImageNames({ L"Img_BG_Event", L"Img_Gradient02"});
	return CImage::PreInitialize();
}

HRESULT Client::CItemInfoLevelImage::Initialize()
{
	switch (m_eItemInfoLevelImageType)
	{
	case Client::EItemInfoLevelImageType::BACKGROUND:
		SetPivot({ 766.0f, 418.0f });
		SetWidth(256.0f);
		SetHeight(87.0f);
		SetTextureIndex(0);
		break;

	case Client::EItemInfoLevelImageType::LINE:
		SetPivot({ 776.0f, 433.0f });
		SetWidth(14.0f);
		SetHeight(60.0f);
		SetTextureIndex(1);
		break;

	default:
		CHECK(false);
		break;
	}
	return CImage::Initialize();
}

HRESULT Client::CItemInfoLevelImage::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CItemInfoLevelImage::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CItemInfoLevelImage::PreTick(float _fDeltaSeconds)
{
	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CItemInfoLevelImage::Tick(float _fDeltaSeconds)
{
	switch (CImage::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CItemInfoLevelImage::PostTick(float _fDeltaSeconds)
{
	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CItemInfoLevelImage::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CItemInfoLevelImage::Render()
{
	CImage::Render();
}

void Client::CItemInfoLevelImage::Release()
{
	CImage::Release();
}
