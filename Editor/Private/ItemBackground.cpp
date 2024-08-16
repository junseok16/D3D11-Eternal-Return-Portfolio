#include "pch.h"
#include "ItemBackground.h"

HRESULT Editor::CItemBackground::PreInitialize()
{
	SetActorRenderType(ERenderType::TRANSLUCENT_OBJECT);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetImageNames({ L"Img_MainBg_08" });
	return CImage::PreInitialize();
}

HRESULT Editor::CItemBackground::Initialize()
{
	SetPivot({ 766.0f, 638.0f });
	SetWidth(258.0f);
	SetHeight(82.0f);
	return CImage::Initialize();
}

HRESULT Editor::CItemBackground::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CItemBackground::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CItemBackground::PreTick(float _fDeltaSeconds)
{
	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CItemBackground::Tick(float _fDeltaSeconds)
{
	switch (CImage::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CItemBackground::PostTick(float _fDeltaSeconds)
{
	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CItemBackground::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CItemBackground::Render()
{
	CImage::Render();
}

void Editor::CItemBackground::Release()
{
	CImage::Release();
}
