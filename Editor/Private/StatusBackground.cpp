#include "pch.h"
#include "StatusBackground.h"

HRESULT Editor::CStatusBackground::PreInitialize()
{
	SetActorRenderType(ERenderType::TRANSLUCENT_OBJECT);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetImageNames({ L"Img_MainBg_06" });
	return CImage::PreInitialize();
}

HRESULT Editor::CStatusBackground::Initialize()
{
	SetPivot({ 118.0f, 638.0f });
	SetWidth(333.0f);
	SetHeight(82.0f);
	return CImage::Initialize();
}

HRESULT Editor::CStatusBackground::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CStatusBackground::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CStatusBackground::PreTick(float _fDeltaSeconds)
{
	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CStatusBackground::Tick(float _fDeltaSeconds)
{
	switch (CImage::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CStatusBackground::PostTick(float _fDeltaSeconds)
{
	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CStatusBackground::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CStatusBackground::Render()
{
	CImage::Render();
}

void Editor::CStatusBackground::Release()
{
	CImage::Release();
}
