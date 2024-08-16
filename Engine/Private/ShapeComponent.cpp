#include "pch.h"
#include "ShapeComponent.h"

#include "World.h"
#include "EngineModule.h"
#include "DeviceManager.h"
#include "CameraManager.h"

#include "ShaderHandler.h"

HRESULT Engine::CShapeComponent::PreInitializeComponent()
{
	if (FAILED(CPrimitiveComponent::PreInitializeComponent())) { return E_FAIL; }
	
	shared_ptr<CDeviceManager> spDeviceManager = CWorld::GetInstance()->GetEngineModule()->GetDeviceManager();
	m_cpDevice = spDeviceManager->GetDevice();
	m_cpDeviceContext = spDeviceManager->GetDeviceContext();
	
	shared_ptr<CShaderHandler> spShaderHandler = CShaderHandler::GetInstance();
	m_cpInputLayout = spShaderHandler->FindInputLayout(L"VertexPositionColor");
	m_spPrimitiveBatch = spShaderHandler->GetPrimitiveBatch();
	m_spBasicEffect = spShaderHandler->GetBasicEffect();

	return S_OK;
}

HRESULT Engine::CShapeComponent::InitializeComponent()
{
	if (FAILED(CPrimitiveComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CShapeComponent::PostInitializeComponent()
{
	if (FAILED(CPrimitiveComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CShapeComponent::BeginPlay()
{
	if (FAILED(CPrimitiveComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CShapeComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CPrimitiveComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CShapeComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CPrimitiveComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CShapeComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CPrimitiveComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	m_usetShapeComponents.empty() ? m_bCollided = false : m_bCollided = true;
	return 0;
}

HRESULT Engine::CShapeComponent::EndPlay()
{
	if (FAILED(CPrimitiveComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CShapeComponent::Render()
{
	CPrimitiveComponent::Render();
}

void Engine::CShapeComponent::Release()
{
	CPrimitiveComponent::Release();
	
	m_usetShapeComponents.clear();

	m_spPrimitiveBatch = nullptr;
	m_spBasicEffect = nullptr;
	m_cpInputLayout = nullptr;
	m_cpDeviceContext = nullptr;
	m_cpDevice = nullptr;
}

bool Engine::CShapeComponent::IsCollisionFlagIntersect(const std::shared_ptr<CShapeComponent> _spShapeComponent)
{
	// 콜리전 레이어 타입을 불러옵니다.
	uint32 iCollisionLayer = static_cast<uint32>(_spShapeComponent->GetCollisionLayer());

	// 콜리전 레이어가 서로 충돌하도록 설정된 경우, 참을 반환합니다.
	if (m_iCollisionFlag & (1 << iCollisionLayer)) { return true; }

	return false;
}

void Engine::CShapeComponent::AddCollisionFlag(ECollisionLayer _eCollisionLayer)
{
	m_iCollisionFlag |= (1 << (uint32)_eCollisionLayer);
}

void Engine::CShapeComponent::RemoveCollisionFlag(ECollisionLayer _eCollisionLayer)
{
	m_iCollisionFlag &= ~(1 << (uint32)_eCollisionLayer);
}
