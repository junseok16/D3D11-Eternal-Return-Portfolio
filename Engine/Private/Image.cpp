#include "pch.h"
#include "Image.h"

#include "GeometryComponent.h"

HRESULT Engine::CImage::PreInitialize()
{
	if (FAILED(CUI::PreInitialize())) { return E_FAIL; }

	m_wpGeometryComponent = CreateActorComponent<CGeometryComponent>(L"GeometryComponent", EComponentType::GEOMETRY);
	SetRootComponent(m_wpGeometryComponent.lock());

	switch (m_ePrimitiveType)
	{
	case Engine::EPrimitiveType::POINT:
		m_wpGeometryComponent.lock()->SetPrimitiveType(EPrimitiveType::POINT);
		m_wpGeometryComponent.lock()->SetTextureNames(m_vecImageNames);
		m_wpGeometryComponent.lock()->SetVertexShaderDesc(L"VS_Point2Rect");
		
		if (!m_wstrPixelShaderName.empty())
		{
			m_wpGeometryComponent.lock()->SetPixelShaderDesc(m_wstrPixelShaderName);
		}
		else
		{
			m_wpGeometryComponent.lock()->SetPixelShaderDesc(L"PS_Point2Rect");
		}
		
		m_wpGeometryComponent.lock()->SetGeometryShaderDesc(L"GS_Point2Rect");
		break;

	case Engine::EPrimitiveType::RECT:
	case Engine::EPrimitiveType::CUBE:
		m_wpGeometryComponent.lock()->SetPrimitiveType(m_ePrimitiveType);
		m_wpGeometryComponent.lock()->SetTextureNames(m_vecImageNames);
		m_wpGeometryComponent.lock()->SetVertexShaderDesc(m_wstrVertexShaderName);
		m_wpGeometryComponent.lock()->SetPixelShaderDesc(m_wstrPixelShaderName);
		m_wpGeometryComponent.lock()->SetGeometryShaderDesc(m_wstrGeometryShaderName);
		break;

	default:
		CHECKF(false, L"Image's primitive type is not designated.")
		break;
	}

	return S_OK;
}

HRESULT Engine::CImage::Initialize()
{
	if (FAILED(CUI::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CImage::PostInitialize()
{
	if (FAILED(CUI::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CImage::BeginPlay()
{
	if (FAILED(CUI::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CImage::PreTick(float _fDeltaSeconds)
{
	if (!m_bActive) { return 0; }

	switch (CUI::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CImage::Tick(float _fDeltaSeconds)
{
	if (!m_bActive) { return 0; }

	switch (CUI::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CImage::PostTick(float _fDeltaSeconds)
{
	if (!m_bActive) { return 0; }

	switch (CUI::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Engine::CImage::EndPlay()
{
	if (FAILED(CUI::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CImage::Render()
{
	if (!m_bActive) { return; }

	CUI::Render();
}

void Engine::CImage::Release()
{
	CUI::Release();
}

void Engine::CImage::SetTextureIndex(uint32 _iTextureIndex)
{
	m_wpGeometryComponent.lock()->SetTextureIndex(_iTextureIndex);
}
