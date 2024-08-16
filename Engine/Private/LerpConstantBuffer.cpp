#include "pch.h"
#include "LerpConstantBuffer.h"

// manager
#include "DeviceManager.h"

// handler
#include "ShaderHandler.h"

#include "Actor.h"

HRESULT Engine::CLerpConstantBuffer::Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint)
{
	if (FAILED(CConstantBuffer::Initialize(_spOwnerActor, _wstrConstantBufferName, _iBindPoint))) { return E_FAIL; }

	return S_OK;
}

void Engine::CLerpConstantBuffer::Release()
{
	CConstantBuffer::Release();
}

void Engine::CLerpConstantBuffer::TickConstantBuffer(uint32 _iIndex)
{
	m_tLerpConstantBuffer.m_iDayType = m_wpOwnerActor.lock()->GetDayNightType();
	m_tLerpConstantBuffer.m_fDayTime = m_wpOwnerActor.lock()->GetDayTime();
	m_tLerpConstantBuffer.m_fNightTime = m_wpOwnerActor.lock()->GetNightTime();
}

void Engine::CLerpConstantBuffer::CopyConstantBuffer(uint32 _iIndex)
{
	m_wpShaderHandler.lock()->CopyConstantBuffer<FLerpConstantBuffer>(m_cpBuffer, m_tLerpConstantBuffer);
}
