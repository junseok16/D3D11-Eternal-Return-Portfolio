#include "pch.h"
#include "HPBarSlider.h"

#include "GameManager.h"
#include "Survivor.h"

HRESULT Client::CHPBarSlider::PreInitialize()
{
	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetFrontSliderName(L"Img_Main_Gage_01");

	m_wpGameManager = CGameManager::GetInstance();
	m_wpSurvivor = m_wpGameManager.lock()->GetSurvivor();

	return CSlider::PreInitialize();
}

HRESULT Client::CHPBarSlider::Initialize()
{
	SetPivot({ 460.0f, 697.0f });
	SetWidth(297.0f);
	SetHeight(9.0f);
	SetMaxWidth(297.0f);
	SetMaxHeight(9.0f);
	return CSlider::Initialize();
}

HRESULT Client::CHPBarSlider::PostInitialize()
{
	if (FAILED(CSlider::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CHPBarSlider::BeginPlay()
{
	if (FAILED(CSlider::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CHPBarSlider::PreTick(float _fDeltaSeconds)
{
	switch (CSlider::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CHPBarSlider::Tick(float _fDeltaSeconds)
{
	switch (CSlider::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CHPBarSlider::PostTick(float _fDeltaSeconds)
{
	switch (CSlider::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	TickSlider();
	return 0;
}

HRESULT Client::CHPBarSlider::EndPlay()
{
	if (FAILED(CSlider::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CHPBarSlider::Render()
{
	CSlider::Render();
}

void Client::CHPBarSlider::Release()
{
	CSlider::Release();
}

void Client::CHPBarSlider::TickSlider()
{
	float fCurHP = m_wpGameManager.lock()->GetSurvivor()->GetCurHP();
	float fMaxHP = m_wpGameManager.lock()->GetSurvivor()->GetMaxHP();

	if (fCurHP <= 0.0f) { fCurHP = 0.0f; }
	m_fWidth = m_fMaxWidth * fCurHP / fMaxHP;
}
