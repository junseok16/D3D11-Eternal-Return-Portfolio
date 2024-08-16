#include "pch.h"
#include "WorldInvTransWorldViewProjectionConstantBuffer.h"

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

HRESULT Engine::CWorldInvTransWorldViewProjectionConstantBuffer::Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint)
{
	if (FAILED(CConstantBuffer::Initialize(_spOwnerActor, _wstrConstantBufferName, _iBindPoint))) { return E_FAIL; }

	m_wpCameraManager = CWorld::GetInstance()->GetEngineModule()->GetCameraManager();
	CHECK(!m_wpCameraManager.expired());
	return S_OK;
}

void Engine::CWorldInvTransWorldViewProjectionConstantBuffer::Release()
{
	CConstantBuffer::Release();
}

void Engine::CWorldInvTransWorldViewProjectionConstantBuffer::TickConstantBuffer(uint32 _iIndex)
{
	// 컴포넌트의 월드 좌표입니다.
	m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matWorld = m_wpOwnerActor.lock()->GetActorWorldMatrix().value();
	m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matWorld.Transpose(m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matWorld);

	// 법선 벡터를 월드 공간으로 변환하려면 월드 행렬의 역전치 행렬을 곱합니다.
	m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matInverseTransposeWorld = m_wpOwnerActor.lock()->GetActorWorldMatrix().value();
	m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matInverseTransposeWorld.Translation(Vector3(0.0f));
	m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matInverseTransposeWorld.Invert(m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matInverseTransposeWorld);

	// 현재 카메라 매니저가 갖고 있는 뷰 행렬, 프로젝션 행렬
	m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matView = m_wpCameraManager.lock()->GetCurViewMatrix();
	m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matView.Transpose(m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matView);

	m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matProjection = m_wpCameraManager.lock()->GetCurPerspectiveProjectionMatrix();
	m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matProjection.Transpose(m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matProjection);
}

void Engine::CWorldInvTransWorldViewProjectionConstantBuffer::CopyConstantBuffer(uint32 _iIndex)
{
	m_wpShaderHandler.lock()->CopyConstantBuffer<FWorldInvTransWorldViewProjectionConstantBuffer>(m_cpBuffer, m_tWorldInvTransWorldViewProjectionConstantBuffer);
}
