#include "pch.h"
#include "ViewProjectionConstantBuffer.h"

// module
#include "EngineModule.h"

// manager
#include "DeviceManager.h"

// world
#include "World.h"

// manager
#include "CameraManager.h"

// handler
#include "ShaderHandler.h"

HRESULT Engine::CViewProjectionConstantBuffer::Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint)
{
	if (FAILED(CConstantBuffer::Initialize(_spOwnerActor, _wstrConstantBufferName, _iBindPoint))) { return E_FAIL; }

	m_wpCameraManager = CWorld::GetInstance()->GetEngineModule()->GetCameraManager();
	CHECK(!m_wpCameraManager.expired());
	return S_OK;
}

void Engine::CViewProjectionConstantBuffer::Release()
{
	CConstantBuffer::Release();
}

void Engine::CViewProjectionConstantBuffer::TickConstantBuffer(uint32 _iIndex)
{
	m_tViewProjectionConstantBuffer.m_matView = m_wpCameraManager.lock()->GetCurViewMatrix();
	m_tViewProjectionConstantBuffer.m_matView.Transpose(m_tViewProjectionConstantBuffer.m_matView);

	m_tViewProjectionConstantBuffer.m_matProjection = m_wpCameraManager.lock()->GetCurOrthogonalProjectionMatrix();
	m_tViewProjectionConstantBuffer.m_matProjection.Transpose(m_tViewProjectionConstantBuffer.m_matProjection);
}

void Engine::CViewProjectionConstantBuffer::CopyConstantBuffer(uint32 _iIndex)
{
	m_wpShaderHandler.lock()->CopyConstantBuffer<FViewProjectionConstantBuffer>(m_cpBuffer, m_tViewProjectionConstantBuffer);
}
