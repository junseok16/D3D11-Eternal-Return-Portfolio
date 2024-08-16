#include "pch.h"
#include "TextureConstantBuffer.h"

// manager
#include "DeviceManager.h"

// handler
#include "ShaderHandler.h"


HRESULT Engine::CTextureConstantBuffer::Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint)
{
	if (FAILED(CConstantBuffer::Initialize(_spOwnerActor, _wstrConstantBufferName, _iBindPoint))) { return E_FAIL; }
	return S_OK;
}

void Engine::CTextureConstantBuffer::Release()
{
	CConstantBuffer::Release();
}

void Engine::CTextureConstantBuffer::TickConstantBuffer(uint32 _iIndex)
{

}

void Engine::CTextureConstantBuffer::CopyConstantBuffer(uint32 _iIndex)
{
	m_wpShaderHandler.lock()->CopyConstantBuffer<FTextureConstantBuffer>(m_cpBuffer, m_tTextureConstantBuffer);
}
