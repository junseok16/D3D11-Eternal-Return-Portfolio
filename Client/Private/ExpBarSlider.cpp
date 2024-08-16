#include "pch.h"
#include "ExpBarSlider.h"

#include "GameManager.h"
#include "Survivor.h"

HRESULT Client::CExpBarSlider::PreInitialize()
{
	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetFrontSliderName(L"Img_Main_Gage_03");

	m_wpGameManager = CGameManager::GetInstance();
	m_wpSurvivor = m_wpGameManager.lock()->GetSurvivor();

	return CSlider::PreInitialize();
}

HRESULT Client::CExpBarSlider::Initialize()
{
	SetPivot({ 233.0f, 710.0f });
	SetWidth(77.0f);
	SetHeight(8.0f);
	SetMaxWidth(77.0f);
	SetMaxHeight(8.0f);
	return CSlider::Initialize();
}

HRESULT Client::CExpBarSlider::PostInitialize()
{
	if (FAILED(CSlider::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CExpBarSlider::BeginPlay()
{
	if (FAILED(CSlider::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CExpBarSlider::PreTick(float _fDeltaSeconds)
{
	switch (CSlider::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CExpBarSlider::Tick(float _fDeltaSeconds)
{
	switch (CSlider::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CExpBarSlider::PostTick(float _fDeltaSeconds)
{
	switch (CSlider::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	TickSlider();
	return 0;
}

HRESULT Client::CExpBarSlider::EndPlay()
{
	if (FAILED(CSlider::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CExpBarSlider::Render()
{
	CSlider::Render();
}

void Client::CExpBarSlider::Release()
{
	CSlider::Release();
}

void Client::CExpBarSlider::TickSlider()
{
	float fCurExp = m_wpGameManager.lock()->GetSurvivor()->GetCurExp();
	float fMaxExp = m_wpGameManager.lock()->GetSurvivor()->GetMaxExp();

	if (fCurExp <= 0.0f) { fCurExp = 0.0f; }
	m_fWidth = m_fMaxWidth * fCurExp / fMaxExp;
}
