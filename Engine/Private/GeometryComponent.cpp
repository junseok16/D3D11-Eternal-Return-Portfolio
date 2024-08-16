#include "pch.h"
#include "GeometryComponent.h"

#include "PrimitiveMeshData.h"

HRESULT Engine::CGeometryComponent::PreInitializeComponent()
{
	if (FAILED(CMeshComponent::PreInitializeComponent())) { return E_FAIL; }
	m_spPrimitiveMeshData = CPrimitiveMeshData::Create
	(
		static_pointer_cast<CSceneComponent>(shared_from_this()),
		m_ePrimitiveType,
		m_vecTextureNames,
		m_wstrVertexShaderDesc,
		m_wstrPixelShaderDesc,
		m_wstrGeometryShaderDesc
	);

	return S_OK;
}

HRESULT Engine::CGeometryComponent::InitializeComponent()
{
	if (FAILED(CMeshComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CGeometryComponent::PostInitializeComponent()
{
	if (FAILED(CMeshComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CGeometryComponent::BeginPlay()
{
	if (FAILED(CMeshComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CGeometryComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CMeshComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CGeometryComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CMeshComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CGeometryComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CMeshComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	m_spPrimitiveMeshData->Tick();
	return 0;
}

HRESULT Engine::CGeometryComponent::EndPlay()
{
	if (FAILED(CMeshComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CGeometryComponent::Render()
{
	CMeshComponent::Render();

	m_spPrimitiveMeshData->Render(m_iTextureIndex);
}

void Engine::CGeometryComponent::Release()
{
	m_spPrimitiveMeshData->Release();
	m_spPrimitiveMeshData = nullptr;

	CMeshComponent::Release();
}

void Engine::CGeometryComponent::SetTextureIndex(uint32 _iTextureIndex)
{
	m_iTextureIndex = _iTextureIndex;
}
