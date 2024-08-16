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
	// ������Ʈ�� ���� ��ǥ�Դϴ�.
	m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matWorld = m_wpOwnerActor.lock()->GetActorWorldMatrix().value();
	m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matWorld.Transpose(m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matWorld);

	// ���� ���͸� ���� �������� ��ȯ�Ϸ��� ���� ����� ����ġ ����� ���մϴ�.
	m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matInverseTransposeWorld = m_wpOwnerActor.lock()->GetActorWorldMatrix().value();
	m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matInverseTransposeWorld.Translation(Vector3(0.0f));
	m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matInverseTransposeWorld.Invert(m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matInverseTransposeWorld);

	// ���� ī�޶� �Ŵ����� ���� �ִ� �� ���, �������� ���
	m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matView = m_wpCameraManager.lock()->GetCurViewMatrix();
	m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matView.Transpose(m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matView);

	m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matProjection = m_wpCameraManager.lock()->GetCurPerspectiveProjectionMatrix();
	m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matProjection.Transpose(m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matProjection);
}

void Engine::CWorldInvTransWorldViewProjectionConstantBuffer::CopyConstantBuffer(uint32 _iIndex)
{
	m_wpShaderHandler.lock()->CopyConstantBuffer<FWorldInvTransWorldViewProjectionConstantBuffer>(m_cpBuffer, m_tWorldInvTransWorldViewProjectionConstantBuffer);
}
