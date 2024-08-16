#include "pch.h"
#include "DeferredWorldViewProjectionConstantBuffer.h"

// handler
#include "ShaderHandler.h"

// manager
#include "DeviceManager.h"

HRESULT Engine::CDeferredWorldViewProjectionConstantBuffer::Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint)
{
	if (FAILED(CConstantBuffer::Initialize(_spOwnerActor, _wstrConstantBufferName, _iBindPoint))) { return E_FAIL; }

	return S_OK;
}

void Engine::CDeferredWorldViewProjectionConstantBuffer::Release()
{
	CConstantBuffer::Release();
}

void Engine::CDeferredWorldViewProjectionConstantBuffer::TickConstantBuffer(uint32 _iIndex)
{

}

void Engine::CDeferredWorldViewProjectionConstantBuffer::CopyConstantBuffer(uint32 _iIndex)
{
	m_wpShaderHandler.lock()->CopyConstantBuffer<FWorldViewProjectionConstantBuffer>(m_cpBuffer, m_tWorldViewProjectionConstantBuffer);
}
