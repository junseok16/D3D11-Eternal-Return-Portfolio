#include "pch.h"
#include "ItemBoxBackground.h"

HRESULT Editor::CItemBoxBackground::PreInitialize()
{
	SetActorRenderType(ERenderType::TRANSLUCENT_OBJECT);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetImageNames({ L"Img_Popup_Panel" });
	return CImage::PreInitialize();
}

HRESULT Editor::CItemBoxBackground::Initialize()
{
	SetPivot({ 868.0f, 476.0f });
	SetWidth(220.0f);
	SetHeight(126.0f);
	return CImage::Initialize();
}

HRESULT Editor::CItemBoxBackground::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CItemBoxBackground::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CItemBoxBackground::PreTick(float _fDeltaSeconds)
{
	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CItemBoxBackground::Tick(float _fDeltaSeconds)
{
	switch (CImage::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CItemBoxBackground::PostTick(float _fDeltaSeconds)
{
	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CItemBoxBackground::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CItemBoxBackground::Render()
{
	CImage::Render();
}

void Editor::CItemBoxBackground::Release()
{
	CImage::Release();
}
