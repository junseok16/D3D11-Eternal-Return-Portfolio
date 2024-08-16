#include "pch.h"
#include "WorldViewProjectionConstantBuffer.h"

// module
#include "EngineModule.h"

// manager
#include "DeviceManager.h"

// world
#include "World.h"

// manager
#include "CameraManager.h"

#include "Actor.h"

// handler
#include "ShaderHandler.h"

HRESULT Engine::CWorldViewProjectionConstantBuffer::Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint)
{
	if (FAILED(CConstantBuffer::Initialize(_spOwnerActor, _wstrConstantBufferName, _iBindPoint))) { return E_FAIL; }

	m_wpCameraManager = CWorld::GetInstance()->GetEngineModule()->GetCameraManager();
	CHECK(!m_wpCameraManager.expired());
	return S_OK;
}

void Engine::CWorldViewProjectionConstantBuffer::Release()
{
	CConstantBuffer::Release();
}

void Engine::CWorldViewProjectionConstantBuffer::TickConstantBuffer(uint32 _iIndex)
{
	// 셰이더에 전달하려면 전치 행렬로 변환해야 합니다.
	m_tWorldViewProjectionConstantBuffer.m_matWorld = m_wpOwnerActor.lock()->GetActorWorldMatrix().value();
	m_tWorldViewProjectionConstantBuffer.m_matWorld.Transpose(m_tWorldViewProjectionConstantBuffer.m_matWorld);

	m_tWorldViewProjectionConstantBuffer.m_matView = m_wpCameraManager.lock()->GetCurViewMatrix();
	m_tWorldViewProjectionConstantBuffer.m_matView.Transpose(m_tWorldViewProjectionConstantBuffer.m_matView);

	m_tWorldViewProjectionConstantBuffer.m_matProjection = m_wpCameraManager.lock()->GetCurPerspectiveProjectionMatrix();
	m_tWorldViewProjectionConstantBuffer.m_matProjection.Transpose(m_tWorldViewProjectionConstantBuffer.m_matProjection);
}

void Engine::CWorldViewProjectionConstantBuffer::CopyConstantBuffer(uint32 _iIndex)
{
	m_wpShaderHandler.lock()->CopyConstantBuffer<FWorldViewProjectionConstantBuffer>(m_cpBuffer, m_tWorldViewProjectionConstantBuffer);
}
