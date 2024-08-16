#include "pch.h"
#include "CameraPositionConstantBuffer.h"

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

HRESULT Engine::CCameraPositionConstantBuffer::Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint)
{
	if (FAILED(CConstantBuffer::Initialize(_spOwnerActor, _wstrConstantBufferName, _iBindPoint))) { return E_FAIL; }

	m_wpCameraManager = CWorld::GetInstance()->GetEngineModule()->GetCameraManager();
	CHECK(!m_wpCameraManager.expired());
	return S_OK;
}

void Engine::CCameraPositionConstantBuffer::Release()
{
	CConstantBuffer::Release();
}

void Engine::CCameraPositionConstantBuffer::TickConstantBuffer(uint32 _iIndex)
{
	// 셰이더에 전달하려면 전치 행렬로 변환해야 합니다.
	Vector3 v3CameraPosition = m_wpCameraManager.lock()->GetCurCameraPosition();
	Vector3 v3CameraForward = m_wpCameraManager.lock()->GetCurCameraForward();

	Vector4 v4CameraPosition = { v3CameraPosition.x, v3CameraPosition.y, v3CameraPosition.z, 1.0f };
	Vector4 v4CameraForward = { v3CameraForward.x, v3CameraForward.y, v3CameraForward.z, 0.0f };
	v4CameraForward.Normalize();

	m_tCameraPositionConstantBuffer.m_vCameraPosition = v4CameraPosition;
	m_tCameraPositionConstantBuffer.m_vCameraForward = v4CameraForward;
}

void Engine::CCameraPositionConstantBuffer::CopyConstantBuffer(uint32 _iIndex)
{
	m_wpShaderHandler.lock()->CopyConstantBuffer<FCameraPosition>(m_cpBuffer, m_tCameraPositionConstantBuffer);
}
