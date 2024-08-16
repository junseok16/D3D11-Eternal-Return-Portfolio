#include "pch.h"
#include "BillboardProjectileConstantBuffer.h"

// world
#include "World.h"

// module
#include "EngineModule.h"

// manager
#include "DeviceManager.h"
#include "CameraManager.h"

// handler
#include "ShaderHandler.h"

HRESULT Engine::CBillboardProjectileConstantBuffer::Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint)
{
	if (FAILED(CConstantBuffer::Initialize(_spOwnerActor, _wstrConstantBufferName, _iBindPoint))) { return E_FAIL; }

	m_wpWorld = CWorld::GetInstance();
	m_wpCameraManager = m_wpWorld.lock()->GetEngineModule()->GetCameraManager();
	CHECK(!m_wpCameraManager.expired());
	return S_OK;
}

void Engine::CBillboardProjectileConstantBuffer::Release()
{
	CConstantBuffer::Release();
}

void Engine::CBillboardProjectileConstantBuffer::TickConstantBuffer(uint32 _iIndex)
{
	m_tBillboardProjectileConstantBuffer.m_vCameraPosition = m_wpCameraManager.lock()->GetCurCameraPosition();
	m_tBillboardProjectileConstantBuffer.m_fWidth = 3.0f;
	
	m_tBillboardProjectileConstantBuffer.m_matView = m_wpCameraManager.lock()->GetCurViewMatrix();
	m_tBillboardProjectileConstantBuffer.m_matView.Transpose(m_tBillboardProjectileConstantBuffer.m_matView);

	m_tBillboardProjectileConstantBuffer.m_matProjection = m_wpCameraManager.lock()->GetCurPerspectiveProjectionMatrix();
	m_tBillboardProjectileConstantBuffer.m_matProjection.Transpose(m_tBillboardProjectileConstantBuffer.m_matProjection);

	m_fSumDeltaSeconds += m_wpWorld.lock()->GetCurDeltaSeconds();
	m_tBillboardProjectileConstantBuffer.m_fDeltaSeconds = m_fSumDeltaSeconds;
}

void Engine::CBillboardProjectileConstantBuffer::CopyConstantBuffer(uint32 _iIndex)
{
	m_wpShaderHandler.lock()->CopyConstantBuffer<FBillboardProjectileConstantBuffer>(m_cpBuffer, m_tBillboardProjectileConstantBuffer);
}
