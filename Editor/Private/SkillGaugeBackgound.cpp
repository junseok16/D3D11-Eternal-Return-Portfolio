#include "pch.h"
#include "SkillGaugeBackgound.h"

HRESULT Editor::CSkillGaugeBackgound::PreInitialize()
{
	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetImageNames({ L"Img_MainBg_07" });
	return CImage::PreInitialize();
}

HRESULT Editor::CSkillGaugeBackgound::Initialize()
{
	return E_NOTIMPL;
}

HRESULT Editor::CSkillGaugeBackgound::PostInitialize()
{
	return E_NOTIMPL;
}

HRESULT Editor::CSkillGaugeBackgound::BeginPlay()
{
	return E_NOTIMPL;
}

int32 Editor::CSkillGaugeBackgound::PreTick(float _fDeltaSeconds)
{
	return int32();
}

int32 Editor::CSkillGaugeBackgound::Tick(float _fDeltaSeconds)
{
	return int32();
}

int32 Editor::CSkillGaugeBackgound::PostTick(float _fDeltaSeconds)
{
	return int32();
}

HRESULT Editor::CSkillGaugeBackgound::EndPlay()
{
	return E_NOTIMPL;
}

void Editor::CSkillGaugeBackgound::Render()
{
}

void Editor::CSkillGaugeBackgound::Release()
{
}
