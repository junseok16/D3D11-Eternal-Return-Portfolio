#include "pch.h"
#include "ColorConstantBuffer.h"

// manager
#include "DeviceManager.h"

// handler
#include "ShaderHandler.h"

#include "Actor.h"

HRESULT Engine::CColorConstantBuffer::Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint)
{
	if (FAILED(CConstantBuffer::Initialize(_spOwnerActor, _wstrConstantBufferName, _iBindPoint))) { return E_FAIL; }

	return S_OK;
}

void Engine::CColorConstantBuffer::Release()
{
	CConstantBuffer::Release();
}

void Engine::CColorConstantBuffer::TickConstantBuffer(uint32 _iIndex)
{
	m_tColorConstantBuffer.m_vColor = m_wpOwnerActor.lock()->GetActorColor();
}

void Engine::CColorConstantBuffer::CopyConstantBuffer(uint32 _iIndex)
{
	m_wpShaderHandler.lock()->CopyConstantBuffer<FColorConstantBuffer>(m_cpBuffer, m_tColorConstantBuffer);
}
