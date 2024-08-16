#include "pch.h"
#include "SkillGaugeBackgound.h"

HRESULT Client::CSkillGaugeBackgound::PreInitialize()
{
	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetImageNames({ L"Img_MainBg_07" });
	return CImage::PreInitialize();
}

HRESULT Client::CSkillGaugeBackgound::Initialize()
{
	return E_NOTIMPL;
}

HRESULT Client::CSkillGaugeBackgound::PostInitialize()
{
	return E_NOTIMPL;
}

HRESULT Client::CSkillGaugeBackgound::BeginPlay()
{
	return E_NOTIMPL;
}

int32 Client::CSkillGaugeBackgound::PreTick(float _fDeltaSeconds)
{
	return int32();
}

int32 Client::CSkillGaugeBackgound::Tick(float _fDeltaSeconds)
{
	return int32();
}

int32 Client::CSkillGaugeBackgound::PostTick(float _fDeltaSeconds)
{
	return int32();
}

HRESULT Client::CSkillGaugeBackgound::EndPlay()
{
	return E_NOTIMPL;
}

void Client::CSkillGaugeBackgound::Render()
{
}

void Client::CSkillGaugeBackgound::Release()
{
}
