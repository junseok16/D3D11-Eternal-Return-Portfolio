#include "pch.h"
#include "StaminaBarSlider.h"

#include "GameManager.h"
#include "Survivor.h"

HRESULT Editor::CStaminaBarSlider::PreInitialize()
{
	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetFrontSliderName(L"Img_Main_Gage_02");

	m_wpGameManager = CGameManager::GetInstance();
	m_wpSurvivor = m_wpGameManager.lock()->GetSurvivor();
	// m_wpSurvivor = dynamic_pointer_cast<CSurvivor>(m_wpActor.lock());

	return CSlider::PreInitialize();
}

HRESULT Editor::CStaminaBarSlider::Initialize()
{
	SetPivot({ 460.0f, 707.0f });
	SetWidth(297.0f);
	SetHeight(8.0f);
	SetMaxWidth(297.0f);
	SetMaxHeight(8.0f);
	return CSlider::Initialize();
}

HRESULT Editor::CStaminaBarSlider::PostInitialize()
{
	if (FAILED(CSlider::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CStaminaBarSlider::BeginPlay()
{
	if (FAILED(CSlider::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CStaminaBarSlider::PreTick(float _fDeltaSeconds)
{
	switch (CSlider::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CStaminaBarSlider::Tick(float _fDeltaSeconds)
{
	switch (CSlider::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CStaminaBarSlider::PostTick(float _fDeltaSeconds)
{
	switch (CSlider::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	TickSlider();
	return 0;
}

HRESULT Editor::CStaminaBarSlider::EndPlay()
{
	if (FAILED(CSlider::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CStaminaBarSlider::Render()
{
	CSlider::Render();
}

void Editor::CStaminaBarSlider::Release()
{
	CSlider::Release();
}

void Editor::CStaminaBarSlider::TickSlider()
{
	float fCurSP = m_wpGameManager.lock()->GetSurvivor()->GetCurSP();
	float fMaxSP = m_wpGameManager.lock()->GetSurvivor()->GetMaxSP();

	if (fCurSP <= 0.0f) { fCurSP = 0.0f; }
	m_fWidth = m_fMaxWidth * fCurSP / fMaxSP;
}
