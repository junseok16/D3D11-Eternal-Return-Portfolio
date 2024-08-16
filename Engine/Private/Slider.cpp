#include "pch.h"
#include "Slider.h"

#include "GeometryComponent.h"

HRESULT Engine::CSlider::PreInitialize()
{
	m_wpFrontSliderComponent = CreateActorComponent<CGeometryComponent>(L"FrontSliderComponent", EComponentType::GEOMETRY);
	SetRootComponent(m_wpFrontSliderComponent.lock());

	if (m_wstrPixelShaderName.empty()) { m_wstrPixelShaderName = L"PS_Slider"; }
	if (m_wstrGeometryShaderName.empty()) { m_wstrGeometryShaderName = L"GS_Slider"; }

	switch (m_ePrimitiveType)
	{
	case Engine::EPrimitiveType::POINT:
		m_wpFrontSliderComponent.lock()->SetPrimitiveType(EPrimitiveType::POINT);
		m_wpFrontSliderComponent.lock()->SetTextureNames({ m_wstrFrontSliderName });
		m_wpFrontSliderComponent.lock()->SetVertexShaderDesc(L"VS_Slider");
		m_wpFrontSliderComponent.lock()->SetGeometryShaderDesc(m_wstrGeometryShaderName);
		m_wpFrontSliderComponent.lock()->SetPixelShaderDesc(m_wstrPixelShaderName);
		break;

	case Engine::EPrimitiveType::RECT:
	case Engine::EPrimitiveType::CUBE:
		m_wpFrontSliderComponent.lock()->SetPrimitiveType(m_ePrimitiveType);
		m_wpFrontSliderComponent.lock()->SetTextureNames({ m_wstrFrontSliderName });
		m_wpFrontSliderComponent.lock()->SetVertexShaderDesc(m_wstrVertexShaderName);
		m_wpFrontSliderComponent.lock()->SetPixelShaderDesc(m_wstrPixelShaderName);
		break;

	default:
		CHECKF(false, L"Image's primitive type is not designated.")
		break;
	}

	return S_OK;
}

HRESULT Engine::CSlider::Initialize()
{
	if (FAILED(CUI::Initialize())) { return E_FAIL; }
	
	return S_OK;
}

HRESULT Engine::CSlider::PostInitialize()
{
	if (FAILED(CUI::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CSlider::BeginPlay()
{
	if (FAILED(CUI::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CSlider::PreTick(float _fDeltaSeconds)
{
	if (!m_bActive) { return 0; }

	switch (CUI::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CSlider::Tick(float _fDeltaSeconds)
{
	if (!m_bActive) { return 0; }

	switch (CUI::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	// TickSlider();
	return 0;
}

int32 Engine::CSlider::PostTick(float _fDeltaSeconds)
{
	if (!m_bActive) { return 0; }

	switch (CUI::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Engine::CSlider::EndPlay()
{
	if (FAILED(CUI::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CSlider::Render()
{
	if (!m_bActive) { return; }

	CUI::Render();
}

void Engine::CSlider::Release()
{
	CUI::Release();
}

void Engine::CSlider::TickSlider()
{
	return;
}
