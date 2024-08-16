#include "pch.h"
#include "StaticMeshComponent.h"

#include "StaticMeshData.h"

HRESULT Engine::CStaticMeshComponent::PreInitializeComponent()
{
	if (FAILED(CMeshComponent::PreInitializeComponent())) { return E_FAIL; }
	m_spStaticMeshData = CStaticMeshData::Create(static_pointer_cast<CSceneComponent>(shared_from_this()), m_wstrStaticModelDesc, m_wstrVertexShaderDesc, m_wstrPixelShaderDesc);

	return S_OK;
}

HRESULT Engine::CStaticMeshComponent::InitializeComponent()
{
	if (FAILED(CMeshComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CStaticMeshComponent::PostInitializeComponent()
{
	if (FAILED(CMeshComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CStaticMeshComponent::BeginPlay()
{
	if (FAILED(CMeshComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CStaticMeshComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CMeshComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CStaticMeshComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CMeshComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CStaticMeshComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CMeshComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	m_spStaticMeshData->Tick();
	return 0;
}

HRESULT Engine::CStaticMeshComponent::EndPlay()
{
	if (FAILED(CMeshComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CStaticMeshComponent::Render()
{
	CMeshComponent::Render();

	m_spStaticMeshData->Render();
}

void Engine::CStaticMeshComponent::RenderShadow()
{
	CActorComponent::RenderShadow();

	// m_spStaticMeshData->RenderShadow();
}

void Engine::CStaticMeshComponent::Release()
{
	m_spStaticMeshData->Release();
	m_spStaticMeshData = nullptr;

	CMeshComponent::Release();
}

HRESULT Engine::CStaticMeshComponent::ChangeModelDesc(const std::wstring& _wstrModelDesc)
{
	return m_spStaticMeshData->ChangeModelDesc(_wstrModelDesc);
}

/*
HRESULT Engine::CStaticMeshComponent::ChangeVertexShader(const std::wstring& _wstrVertexShaderDesc)
{
	return m_spStaticMeshData->ChangeVertexShader(_wstrVertexShaderDesc);
}

HRESULT Engine::CStaticMeshComponent::ChangePixelShader(const std::wstring& _wstrPixelShaderDesc)
{
	return m_spStaticMeshData->ChangePixelShader(_wstrPixelShaderDesc);
}
*/
