#include "pch.h"
#include "GamePlayBackground.h"

HRESULT Editor::CGamePlayBackground::PreInitialize()
{
	SetActorRenderType(ERenderType::TRANSLUCENT_OBJECT);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetImageNames({ L"Img_HUDBg_02", L"Img_HUDBg_03", L"Img_HUDBg_04" });
	return CImage::PreInitialize();
}

HRESULT Editor::CGamePlayBackground::Initialize()
{
	SetPivot({ 408.0f, 0.0f });
	SetWidth(464.0f);
	SetHeight(80.0f);
	return CImage::Initialize();
}

HRESULT Editor::CGamePlayBackground::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CGamePlayBackground::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CGamePlayBackground::PreTick(float _fDeltaSeconds)
{
	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CGamePlayBackground::Tick(float _fDeltaSeconds)
{
	switch (CImage::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CGamePlayBackground::PostTick(float _fDeltaSeconds)
{
	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CGamePlayBackground::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CGamePlayBackground::Render()
{
	CImage::Render();
}

void Editor::CGamePlayBackground::Release()
{
	CImage::Release();
}
