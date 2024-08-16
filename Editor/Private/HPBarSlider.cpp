#include "pch.h"
#include "HPBarSlider.h"

#include "GameManager.h"
#include "Survivor.h"

HRESULT Editor::CHPBarSlider::PreInitialize()
{
	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetFrontSliderName(L"Img_Main_Gage_01");

	m_wpGameManager = CGameManager::GetInstance();
	m_wpSurvivor = m_wpGameManager.lock()->GetSurvivor();

	return CSlider::PreInitialize();
}

HRESULT Editor::CHPBarSlider::Initialize()
{
	SetPivot({ 460.0f, 697.0f });
	SetWidth(297.0f);
	SetHeight(9.0f);
	SetMaxWidth(297.0f);
	SetMaxHeight(9.0f);
	return CSlider::Initialize();
}

HRESULT Editor::CHPBarSlider::PostInitialize()
{
	if (FAILED(CSlider::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CHPBarSlider::BeginPlay()
{
	if (FAILED(CSlider::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CHPBarSlider::PreTick(float _fDeltaSeconds)
{
	switch (CSlider::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CHPBarSlider::Tick(float _fDeltaSeconds)
{
	switch (CSlider::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CHPBarSlider::PostTick(float _fDeltaSeconds)
{
	switch (CSlider::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	TickSlider();
	return 0;
}

HRESULT Editor::CHPBarSlider::EndPlay()
{
	if (FAILED(CSlider::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CHPBarSlider::Render()
{
	CSlider::Render();
}

void Editor::CHPBarSlider::Release()
{
	CSlider::Release();
}

void Editor::CHPBarSlider::TickSlider()
{
	float fCurHP = m_wpGameManager.lock()->GetSurvivor()->GetCurHP();
	float fMaxHP = m_wpGameManager.lock()->GetSurvivor()->GetMaxHP();

	if (fCurHP <= 0.0f) { fCurHP = 0.0f; }
	m_fWidth = m_fMaxWidth * fCurHP / fMaxHP;
}
