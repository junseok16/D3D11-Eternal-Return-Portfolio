#include "pch.h"
#include "LightConstantBuffer.h"

// module
#include "EngineModule.h"

// world
#include "World.h"

// manager
#include "DeviceManager.h"
#include "LightManager.h"

// component
#include "LightComponent.h"

// handler
#include "ShaderHandler.h"

HRESULT Engine::CLightConstantBuffer::Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint)
{
	if (FAILED(CConstantBuffer::Initialize(_spOwnerActor, _wstrConstantBufferName, _iBindPoint))) { return E_FAIL; }

	m_wpLightManager = CWorld::GetInstance()->GetEngineModule()->GetLightManager();
	CHECK(!m_wpLightManager.expired());
	return S_OK;
}

void Engine::CLightConstantBuffer::Release()
{
	CConstantBuffer::Release();
}

void Engine::CLightConstantBuffer::SetLightDesc(const std::shared_ptr<CLightComponent>& _spLightComponent, ELightType _eLightType)
{
	m_wpLightComponent = _spLightComponent;
	m_eLightType = _eLightType;
}

void Engine::CLightConstantBuffer::TickConstantBuffer(uint32 _iIndex)
{
	TLightDesc tLightDesc = m_wpLightComponent.lock()->GetLightDesc();

	m_tLightConstantBuffer.m_vAmbient = tLightDesc.m_vAmbient;
	m_tLightConstantBuffer.m_vDiffuse = tLightDesc.m_vDiffuse;
	m_tLightConstantBuffer.m_vSpecular = tLightDesc.m_vSpecular;

	m_tLightConstantBuffer.m_fRange = tLightDesc.m_fRange;
	m_tLightConstantBuffer.m_fFallOffBegin = tLightDesc.m_fFallOffBegin;
	m_tLightConstantBuffer.m_fFallOffEnd = tLightDesc.m_fFallOffEnd;

	m_tLightConstantBuffer.m_vPosition = tLightDesc.m_vPosition;
	m_tLightConstantBuffer.m_vDirection = tLightDesc.m_vDirection;
}

void Engine::CLightConstantBuffer::CopyConstantBuffer(uint32 _iIndex)
{
	m_wpShaderHandler.lock()->CopyConstantBuffer<FLightConstantBuffer>(m_cpBuffer, m_tLightConstantBuffer);
}
