#include "pch.h"
#include "SkillBackground.h"

HRESULT Editor::CSkillBackground::PreInitialize()
{
	SetActorRenderType(ERenderType::TRANSLUCENT_OBJECT);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetImageNames({ L"Img_MainBg_07" });
	return CImage::PreInitialize();
}

HRESULT Editor::CSkillBackground::Initialize()
{
	SetPivot({ 454.0f, 638.0f });
	SetWidth(309.0f);
	SetHeight(82.0f);
	return CImage::Initialize();
}

HRESULT Editor::CSkillBackground::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CSkillBackground::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CSkillBackground::PreTick(float _fDeltaSeconds)
{
	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CSkillBackground::Tick(float _fDeltaSeconds)
{
	switch (CImage::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CSkillBackground::PostTick(float _fDeltaSeconds)
{
	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CSkillBackground::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CSkillBackground::Render()
{
	CImage::Render();
}

void Editor::CSkillBackground::Release()
{
	CImage::Release();
}
