#include "pch.h"
#include "InLevelImage.h"

HRESULT Editor::CInLevelImage::PreInitialize()
{
	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	SetPrimitiveType(EPrimitiveType::POINT);

	SetImageNames({ L"Img_ChaLevel_Bg" });

	return CImage::PreInitialize();
}

HRESULT Editor::CInLevelImage::Initialize()
{
	// SetPivot({ todo });
	SetWidth(85.0f);
	SetHeight(15.0f);
	return CImage::Initialize();
}

HRESULT Editor::CInLevelImage::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CInLevelImage::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CInLevelImage::PreTick(float _fDeltaSeconds)
{
	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CInLevelImage::Tick(float _fDeltaSeconds)
{
	switch (CImage::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CInLevelImage::PostTick(float _fDeltaSeconds)
{
	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CInLevelImage::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CInLevelImage::Render()
{
	CImage::Render();
}

void Editor::CInLevelImage::Release()
{
	CImage::Release();
}
