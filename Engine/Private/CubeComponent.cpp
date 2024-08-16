#include "pch.h"
#include "CubeComponent.h"

#include "PrimitiveMeshData.h"

HRESULT Engine::CCubeComponent::PreInitializeComponent()
{
	if (FAILED(CMeshComponent::PreInitializeComponent())) { return E_FAIL; }
	m_spPrimitiveMeshData = CPrimitiveMeshData::Create
	(
		static_pointer_cast<CSceneComponent>(shared_from_this()),
		EPrimitiveType::CUBE,
		m_vecPrimitiveDescs,
		m_wstrVertexShaderDesc,
		m_wstrPixelShaderDesc
	);

	return S_OK;
}

HRESULT Engine::CCubeComponent::InitializeComponent()
{
	if (FAILED(CMeshComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CCubeComponent::PostInitializeComponent()
{
	if (FAILED(CMeshComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CCubeComponent::BeginPlay()
{
	if (FAILED(CMeshComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CCubeComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CMeshComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CCubeComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CMeshComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CCubeComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CMeshComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	m_spPrimitiveMeshData->Tick();
	return 0;
}

HRESULT Engine::CCubeComponent::EndPlay()
{
	if (FAILED(CMeshComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CCubeComponent::Render()
{
	CMeshComponent::Render();

	m_spPrimitiveMeshData->Render(0);
}

void Engine::CCubeComponent::Release()
{
	m_spPrimitiveMeshData->Release();
	m_spPrimitiveMeshData = nullptr;

	CMeshComponent::Release();
}

void Engine::CCubeComponent::SetConstantBuffer(const shared_ptr<CConstantBuffer>& _spConstantBuffer)
{
	m_spPrimitiveMeshData->SetConstantBuffer(_spConstantBuffer);
}
