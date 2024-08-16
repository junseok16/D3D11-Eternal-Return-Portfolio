#include "pch.h"
#include "SphereComponent.h"

// manager
#include "CameraManager.h"

// actor
#include "Actor.h"

// component
#include "AABBComponent.h"
#include "OBBComponent.h"

HRESULT Engine::CSphereComponent::PreInitializeComponent()
{
	if (FAILED(CShapeComponent::PreInitializeComponent())) { return E_FAIL; }
	m_spLocalSphere = make_shared<BoundingSphere>();
	m_spWorldSphere = make_shared<BoundingSphere>();

	m_spLocalSphere->Center = m_spWorldSphere->Center = Vector3::Zero;
	m_spLocalSphere->Radius = m_spWorldSphere->Radius = 1.0f;
	m_eShapeType = EShapeType::SPHERE;
	return S_OK;
}

HRESULT Engine::CSphereComponent::InitializeComponent()
{
	if (FAILED(CShapeComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CSphereComponent::PostInitializeComponent()
{
	if (FAILED(CShapeComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CSphereComponent::BeginPlay()
{
	if (FAILED(CShapeComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CSphereComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CShapeComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	// m_spLocalSphere->Transform(*m_spWorldSphere, m_matWorld);
	return 0;
}

int32 Engine::CSphereComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CShapeComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	m_spLocalSphere->Transform(*m_spWorldSphere, m_matWorld);
	return 0;
}

int32 Engine::CSphereComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CShapeComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Engine::CSphereComponent::EndPlay()
{
	if (FAILED(CShapeComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CSphereComponent::Render()
{
	/*
#ifdef _DEBUG

	if (!m_bActive) { return; }

	m_spBasicEffect->SetWorld(XMMatrixIdentity());

	m_spBasicEffect->SetView(m_wpCameraManager.lock()->GetCurViewMatrix());

	m_spBasicEffect->SetProjection(m_wpCameraManager.lock()->GetCurPerspectiveProjectionMatrix());

	m_spBasicEffect->Apply(m_cpDeviceContext.Get());

	m_cpDeviceContext->IASetInputLayout(m_cpInputLayout.Get());

	m_spPrimitiveBatch->Begin();

	DX::Draw(m_spPrimitiveBatch.get(), *m_spWorldSphere, m_bCollided ? Colors::Red : Colors::Green);

	m_spPrimitiveBatch->End();

#endif
	*/
	CShapeComponent::Render();
}

void Engine::CSphereComponent::Release()
{
	m_spLocalSphere = nullptr;
	m_spWorldSphere = nullptr;
	CShapeComponent::Release();
}

bool Engine::CSphereComponent::IsCollided(const std::shared_ptr<CShapeComponent>& _spShapeComponent)
{
	if (IsCollisionFlagIntersect(_spShapeComponent) == false) { return false; }

	switch (_spShapeComponent->GetShapeType())
	{
	case EShapeType::SPHERE:
	{
		shared_ptr<CSphereComponent> spSphereComponent = static_pointer_cast<CSphereComponent>(_spShapeComponent);
		return m_spWorldSphere->Intersects(*spSphereComponent->GetSphere());
	}

	case EShapeType::AABB:
	{
		shared_ptr<CAABBComponent> spAABBComponent = static_pointer_cast<CAABBComponent>(_spShapeComponent);
		return m_spWorldSphere->Intersects(*spAABBComponent->GetAABB());
	}

	case EShapeType::OBB:
	{
		shared_ptr<COBBComponent> spOBBComponent = static_pointer_cast<COBBComponent>(_spShapeComponent);
		return m_spWorldSphere->Intersects(*spOBBComponent->GetOBB());
	}

	default:
		CHECKF(false, L"The shader type is not designated.");
		break;
	}
	return false;
}
