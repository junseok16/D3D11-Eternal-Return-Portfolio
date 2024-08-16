#include "pch.h"
#include "ViewOrthoProjConstantBuffer.h"

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

HRESULT Engine::CViewOrthoProjConstantBuffer::Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint)
{
	if (FAILED(CConstantBuffer::Initialize(_spOwnerActor, _wstrConstantBufferName, _iBindPoint))) { return E_FAIL; }

	m_wpCameraManager = CWorld::GetInstance()->GetEngineModule()->GetCameraManager();
	CHECK(!m_wpCameraManager.expired());
	return S_OK;
}

void Engine::CViewOrthoProjConstantBuffer::Release()
{
	CConstantBuffer::Release();
}

void Engine::CViewOrthoProjConstantBuffer::TickConstantBuffer(uint32 _iIndex)
{
	m_tViewOrthoProjConstantBuffer.m_matView = Matrix::Identity;
	
	m_tViewOrthoProjConstantBuffer.m_matOrthoProj = m_wpCameraManager.lock()->GetCurOrthogonalProjectionMatrix();
	m_tViewOrthoProjConstantBuffer.m_matOrthoProj.Transpose(m_tViewOrthoProjConstantBuffer.m_matOrthoProj);
}

void Engine::CViewOrthoProjConstantBuffer::CopyConstantBuffer(uint32 _iIndex)
{
	m_wpShaderHandler.lock()->CopyConstantBuffer<FViewOrthoProjConstantBuffer>(m_cpBuffer, m_tViewOrthoProjConstantBuffer);
}
