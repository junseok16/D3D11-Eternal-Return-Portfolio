#include "pch.h"
#include "LightComponent.h"

#include "LightConstantBuffer.h"
#include "InvViewInvProjectionConstantBuffer.h"

HRESULT Engine::CLightComponent::PreInitializeComponent()
{
	if (FAILED(CSceneComponent::PreInitializeComponent())) { return E_FAIL; }
	
	return S_OK;
}

HRESULT Engine::CLightComponent::InitializeComponent()
{
	if (FAILED(CSceneComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CLightComponent::PostInitializeComponent()
{
	if (FAILED(CSceneComponent::PostInitializeComponent())) { return E_FAIL; }

	switch (m_tLightDesc.m_eLightType)
	{
	case ELightType::DIRECTIONAL:
		m_spLightPSConstantBuffers = CConstantBuffer::Create<CLightConstantBuffer>(nullptr, L"CB_Light", 0);
		m_spLightPSConstantBuffers->SetLightDesc(dynamic_pointer_cast<CLightComponent>(shared_from_this()), m_tLightDesc.m_eLightType);
		break;

	case ELightType::POINT:
		m_spLightPSConstantBuffers = CConstantBuffer::Create<CLightConstantBuffer>(nullptr, L"CB_Light", 0);
		m_spLightPSConstantBuffers->SetLightDesc(dynamic_pointer_cast<CLightComponent>(shared_from_this()), m_tLightDesc.m_eLightType);

		m_spInvViewInvProjectionConstantBuffer = CConstantBuffer::Create<CInvViewInvProjectionConstantBuffer>(nullptr, L"CB_InvViewInvProjection", 1);
		break;

	default:
		break;
	}

	return S_OK;
}

HRESULT Engine::CLightComponent::BeginPlay()
{
	if (FAILED(CSceneComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CLightComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CSceneComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CLightComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CSceneComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	switch (m_tLightDesc.m_eLightType)
	{
	case ELightType::SPOT:
		m_tLightDesc.m_vPosition = GetComponentWorldPosition();
		break;

	case ELightType::POINT:
		m_tLightDesc.m_vPosition = GetComponentWorldPosition();
		break;

	case ELightType::DIRECTIONAL:
		break;

	default:
		break;
	}

	return 0;
}

int32 Engine::CLightComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CSceneComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	switch (m_tLightDesc.m_eLightType)
	{
	case ELightType::DIRECTIONAL:
		m_spLightPSConstantBuffers->TickConstantBuffer(0);
		break;

	case ELightType::POINT:
		m_spLightPSConstantBuffers->TickConstantBuffer(0);
		m_spInvViewInvProjectionConstantBuffer->TickConstantBuffer(0);
		break;

	default:
		break;
	}

	return 0;
}

HRESULT Engine::CLightComponent::EndPlay()
{
	if (FAILED(CSceneComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CLightComponent::Render()
{
	CSceneComponent::Render();

	switch (m_tLightDesc.m_eLightType)
	{
	case ELightType::DIRECTIONAL:
		m_spLightPSConstantBuffers->CopyConstantBuffer(0);
		m_spLightPSConstantBuffers->PSSetConstantBuffers();
		break;

	case ELightType::POINT:
		m_spLightPSConstantBuffers->CopyConstantBuffer(0);
		m_spLightPSConstantBuffers->PSSetConstantBuffers();

		m_spInvViewInvProjectionConstantBuffer->CopyConstantBuffer(0);
		m_spInvViewInvProjectionConstantBuffer->PSSetConstantBuffers();
		break;

	default:
		break;
	}
}

void Engine::CLightComponent::Release()
{
	if (m_spLightPSConstantBuffers)
	{
		m_spLightPSConstantBuffers->Release();
		m_spLightPSConstantBuffers = nullptr;
	}

	if (m_spInvViewInvProjectionConstantBuffer)
	{
		m_spInvViewInvProjectionConstantBuffer->Release();
		m_spInvViewInvProjectionConstantBuffer = nullptr;
	}

	CSceneComponent::Release();
}
