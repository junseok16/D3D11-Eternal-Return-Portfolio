#include "pch.h"
#include "InvViewInvProjectionConstantBuffer.h"

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

HRESULT Engine::CInvViewInvProjectionConstantBuffer::Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint)
{
	if (FAILED(CConstantBuffer::Initialize(_spOwnerActor, _wstrConstantBufferName, _iBindPoint))) { return E_FAIL; }

	m_wpCameraManager = CWorld::GetInstance()->GetEngineModule()->GetCameraManager();
	CHECK(!m_wpCameraManager.expired());
	return S_OK;
}

void Engine::CInvViewInvProjectionConstantBuffer::Release()
{
	CConstantBuffer::Release();
}

void Engine::CInvViewInvProjectionConstantBuffer::TickConstantBuffer(uint32 _iIndex)
{
	m_tInvViewInvProjectionConstantBuffer.m_matInvView = m_wpCameraManager.lock()->GetCurViewMatrix();
	m_tInvViewInvProjectionConstantBuffer.m_matInvView.Invert(m_tInvViewInvProjectionConstantBuffer.m_matInvView);
	m_tInvViewInvProjectionConstantBuffer.m_matInvView.Transpose(m_tInvViewInvProjectionConstantBuffer.m_matInvView);

	m_tInvViewInvProjectionConstantBuffer.m_matInvProj = m_wpCameraManager.lock()->GetCurPerspectiveProjectionMatrix();
	m_tInvViewInvProjectionConstantBuffer.m_matInvProj.Invert(m_tInvViewInvProjectionConstantBuffer.m_matInvProj);
	m_tInvViewInvProjectionConstantBuffer.m_matInvProj.Transpose(m_tInvViewInvProjectionConstantBuffer.m_matInvProj);
}

void Engine::CInvViewInvProjectionConstantBuffer::CopyConstantBuffer(uint32 _iIndex)
{
	m_wpShaderHandler.lock()->CopyConstantBuffer<FInvViewInvProjConstantBuffer>(m_cpBuffer, m_tInvViewInvProjectionConstantBuffer);
}
