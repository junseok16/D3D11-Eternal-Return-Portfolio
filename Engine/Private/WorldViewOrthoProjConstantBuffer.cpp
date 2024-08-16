#include "pch.h"
#include "WorldViewOrthoProjConstantBuffer.h"

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

HRESULT Engine::CWorldViewOrthoProjConstantBuffer::Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint)
{
	if (FAILED(CConstantBuffer::Initialize(_spOwnerActor, _wstrConstantBufferName, _iBindPoint))) { return E_FAIL; }

	m_wpCameraManager = CWorld::GetInstance()->GetEngineModule()->GetCameraManager();
	CHECK(!m_wpCameraManager.expired());
	return S_OK;
}

void Engine::CWorldViewOrthoProjConstantBuffer::Release()
{
	CConstantBuffer::Release();
}

void Engine::CWorldViewOrthoProjConstantBuffer::TickConstantBuffer(uint32 _iIndex)
{
	// 셰이더에 전달하려면 전치 행렬로 변환해야 합니다.
	m_tWorldViewOrthoProjConstantBuffer.m_matWorld = m_wpOwnerActor.lock()->GetActorWorldMatrix().value();
	m_tWorldViewOrthoProjConstantBuffer.m_matWorld.Transpose(m_tWorldViewOrthoProjConstantBuffer.m_matWorld);

	m_tWorldViewOrthoProjConstantBuffer.m_matView = m_wpCameraManager.lock()->GetCurViewMatrix();
	m_tWorldViewOrthoProjConstantBuffer.m_matView.Transpose(m_tWorldViewOrthoProjConstantBuffer.m_matView);

	m_tWorldViewOrthoProjConstantBuffer.m_matOrthoProj = m_wpCameraManager.lock()->GetCurOrthogonalProjectionMatrix();
	m_tWorldViewOrthoProjConstantBuffer.m_matOrthoProj.Transpose(m_tWorldViewOrthoProjConstantBuffer.m_matOrthoProj);
}

void Engine::CWorldViewOrthoProjConstantBuffer::CopyConstantBuffer(uint32 _iIndex)
{
	m_wpShaderHandler.lock()->CopyConstantBuffer<FWorldViewOrthoProjConstantBuffer>(m_cpBuffer, m_tWorldViewOrthoProjConstantBuffer);
}
