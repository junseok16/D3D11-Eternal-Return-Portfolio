#include "pch.h"
#include "RimConstantBuffer.h"

// world
#include "World.h"

// module
#include "EngineModule.h"

// manager
#include "DeviceManager.h"
#include "CameraManager.h"

// handler
#include "ShaderHandler.h"

#include "Actor.h"

HRESULT Engine::CRimConstantBuffer::Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint)
{
	if (FAILED(CConstantBuffer::Initialize(_spOwnerActor, _wstrConstantBufferName, _iBindPoint))) { return E_FAIL; }

	m_wpCameraManager = CWorld::GetInstance()->GetEngineModule()->GetCameraManager();
	CHECK(!m_wpCameraManager.expired());
	return S_OK;
}

void Engine::CRimConstantBuffer::Release()
{
	CConstantBuffer::Release();
}

void Engine::CRimConstantBuffer::TickConstantBuffer(uint32 _iIndex)
{
	m_tRimConstantBuffer.m_vCameraWorldPosition = m_wpCameraManager.lock()->GetCurCameraPosition();
	m_tRimConstantBuffer.m_vRimColor = Vector3(m_wpOwnerActor.lock()->GetActorColor());
	m_tRimConstantBuffer.m_fRimStrength;
}

void Engine::CRimConstantBuffer::CopyConstantBuffer(uint32 _iIndex)
{
	m_wpShaderHandler.lock()->CopyConstantBuffer<FRimConstantBuffer>(m_cpBuffer, m_tRimConstantBuffer);
}
