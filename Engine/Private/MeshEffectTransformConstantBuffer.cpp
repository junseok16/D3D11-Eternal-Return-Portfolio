#include "pch.h"
#include "MeshEffectTransformConstantBuffer.h"

// manager
#include "CameraManager.h"
#include "DeviceManager.h"

// module
#include "EngineModule.h"

// world
#include "World.h"

// handler
#include "ShaderHandler.h"

// effect
#include "EffectMeshData.h"

HRESULT Engine::CMeshEffectTransformConstantBuffer::Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint)
{
	if (FAILED(CConstantBuffer::Initialize(_spOwnerActor, _wstrConstantBufferName, _iBindPoint))) { return E_FAIL; }

	m_wpCameraManager = CWorld::GetInstance()->GetEngineModule()->GetCameraManager();
	CHECK(!m_wpCameraManager.expired());
	return S_OK;
}

void Engine::CMeshEffectTransformConstantBuffer::Release()
{
	CConstantBuffer::Release();
}

void Engine::CMeshEffectTransformConstantBuffer::TickConstantBuffer(uint32 _iIndex)
{
	m_tMeshEffectTransformConstantBuffer.m_matWorld = m_wpEffectMeshData.lock()->GetEffectMatrix();
	m_tMeshEffectTransformConstantBuffer.m_matWorld.Transpose(m_tMeshEffectTransformConstantBuffer.m_matWorld);

	m_tMeshEffectTransformConstantBuffer.m_matView = m_wpCameraManager.lock()->GetCurViewMatrix();
	m_tMeshEffectTransformConstantBuffer.m_matView.Transpose(m_tMeshEffectTransformConstantBuffer.m_matView);

	m_tMeshEffectTransformConstantBuffer.m_matProjection = m_wpCameraManager.lock()->GetCurPerspectiveProjectionMatrix();
	m_tMeshEffectTransformConstantBuffer.m_matProjection.Transpose(m_tMeshEffectTransformConstantBuffer.m_matProjection);
}

void Engine::CMeshEffectTransformConstantBuffer::CopyConstantBuffer(uint32 _iIndex)
{
	m_wpShaderHandler.lock()->CopyConstantBuffer<FMeshEffectTransformConstantBuffer>(m_cpBuffer, m_tMeshEffectTransformConstantBuffer);
}
