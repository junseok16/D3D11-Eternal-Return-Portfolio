#include "pch.h"
#include "LightViewLightProjectionConstantBuffer.h"

// manager
#include "DeviceManager.h"

// handler
#include "ShaderHandler.h"

HRESULT Engine::CLightViewLightProjectionConstantBuffer::Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint)
{
	if (FAILED(CConstantBuffer::Initialize(_spOwnerActor, _wstrConstantBufferName, _iBindPoint))) { return E_FAIL; }

	return S_OK;
}

void Engine::CLightViewLightProjectionConstantBuffer::Release()
{
	CConstantBuffer::Release();
}

void Engine::CLightViewLightProjectionConstantBuffer::TickConstantBuffer(uint32 _iIndex)
{
	m_tLightViewLightProjectionConstantBuffer.m_matLightView = XMMatrixLookAtLH(XMVectorSet(20.0f, 100.0f, 20.0f, 1.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	m_tLightViewLightProjectionConstantBuffer.m_matLightView.Transpose(m_tLightViewLightProjectionConstantBuffer.m_matLightView);

	m_tLightViewLightProjectionConstantBuffer.m_matLightProjection = XMMatrixPerspectiveFovLH(XMConvertToRadians(90.0f), 1280.0f / 720.0f, 0.1f, 2000.0f);
	m_tLightViewLightProjectionConstantBuffer.m_matLightProjection.Transpose(m_tLightViewLightProjectionConstantBuffer.m_matLightProjection);
}

void Engine::CLightViewLightProjectionConstantBuffer::CopyConstantBuffer(uint32 _iIndex)
{
	m_wpShaderHandler.lock()->CopyConstantBuffer<FLightViewLightProjectionConstantBuffer>(m_cpBuffer, m_tLightViewLightProjectionConstantBuffer);
}
