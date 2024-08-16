#include "pch.h"
#include "WorldConstantBuffer.h"

// manager
#include "DeviceManager.h"

// actor
#include "Actor.h"

// handler
#include "ShaderHandler.h"

HRESULT Engine::CWorldConstantBuffer::Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint)
{
	if (FAILED(CConstantBuffer::Initialize(_spOwnerActor, _wstrConstantBufferName, _iBindPoint))) { return E_FAIL; }

	return S_OK;
}

void Engine::CWorldConstantBuffer::Release()
{
	CConstantBuffer::Release();
}

void Engine::CWorldConstantBuffer::TickConstantBuffer(uint32 _iIndex)
{
	// 셰이더에 전달하려면 전치 행렬로 변환해야 합니다.
	m_tWorldConstantBuffer.m_matWorld = m_wpOwnerActor.lock()->GetActorWorldMatrix().value();
	m_tWorldConstantBuffer.m_matWorld.Transpose(m_tWorldConstantBuffer.m_matWorld);
}

void Engine::CWorldConstantBuffer::CopyConstantBuffer(uint32 _iIndex)
{
	m_wpShaderHandler.lock()->CopyConstantBuffer<FWorldConstantBuffer>(m_cpBuffer, m_tWorldConstantBuffer);
}
