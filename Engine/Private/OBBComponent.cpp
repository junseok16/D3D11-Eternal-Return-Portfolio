#include "pch.h"
#include "OBBComponent.h"

// manager
#include "CameraManager.h"

// component
#include "SphereComponent.h"
#include "AABBComponent.h"

// actor
#include "Actor.h"

HRESULT Engine::COBBComponent::PreInitializeComponent()
{
	if (FAILED(CShapeComponent::PreInitializeComponent())) { return E_FAIL; }
	m_spLocalOBB = make_shared<BoundingOrientedBox>();
	m_spWorldOBB = make_shared<BoundingOrientedBox>();

	Vector4 vQuat = XMQuaternionRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
	m_spLocalOBB->Center = m_spWorldOBB->Center = Vector3::Zero;
	m_spLocalOBB->Extents = m_spWorldOBB->Extents = Vector3::One;
	m_spLocalOBB->Orientation = m_spWorldOBB->Orientation = vQuat;
	m_eShapeType = EShapeType::OBB;
	return S_OK;
}

HRESULT Engine::COBBComponent::InitializeComponent()
{
	if (FAILED(CShapeComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::COBBComponent::PostInitializeComponent()
{
	if (FAILED(CShapeComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::COBBComponent::BeginPlay()
{
	if (FAILED(CShapeComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::COBBComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CShapeComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::COBBComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CShapeComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	Matrix matWorld = m_wpOwnerActor.lock()->GetActorWorldMatrix().value();
	m_spLocalOBB->Transform(*m_spWorldOBB, matWorld);
	return 0;
}

int32 Engine::COBBComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CShapeComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Engine::COBBComponent::EndPlay()
{
	if (FAILED(CShapeComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::COBBComponent::Render()
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

	DX::Draw(m_spPrimitiveBatch.get(), *m_spWorldOBB, m_bCollided ? Colors::Red : Colors::Green);

	m_spPrimitiveBatch->End();

#endif
*/
	CShapeComponent::Render();
}

void Engine::COBBComponent::Release()
{
	m_spLocalOBB = nullptr;
	m_spWorldOBB = nullptr;
	CShapeComponent::Release();
}

void Engine::COBBComponent::SetCenter(const Vector3& _vCenter)
{
	m_spLocalOBB->Center = _vCenter;
	//m_spWorldOBB->Center = _vCenter;
}

void Engine::COBBComponent::SetExtent(const Vector3& _vExtents)
{
	m_spLocalOBB->Extents = _vExtents;
	//m_spWorldOBB->Extents = _vExtents;
}

void Engine::COBBComponent::SetOrientation(const Vector3& _vOrientation)
{
	Vector4 vQuat = XMQuaternionRotationRollPitchYaw(_vOrientation.x, _vOrientation.y, _vOrientation.z);
	m_spLocalOBB->Orientation = vQuat;
	//m_spWorldOBB->Orientation = vQuat;
}

bool Engine::COBBComponent::IsCollided(const std::shared_ptr<CShapeComponent>& _spShapeComponent)
{
	if (IsCollisionFlagIntersect(_spShapeComponent) == false) { return false; }

	switch (_spShapeComponent->GetShapeType())
	{
	case EShapeType::SPHERE:
	{
		shared_ptr<CSphereComponent> spSphereComponent = static_pointer_cast<CSphereComponent>(_spShapeComponent);
		return m_spWorldOBB->Intersects(*spSphereComponent->GetSphere());
	}

	case EShapeType::AABB:
	{
		shared_ptr<CAABBComponent> spAABBComponent = static_pointer_cast<CAABBComponent>(_spShapeComponent);
		return m_spWorldOBB->Intersects(*spAABBComponent->GetAABB());
	}

	case EShapeType::OBB:
	{
		shared_ptr<COBBComponent> spOBBComponent = static_pointer_cast<COBBComponent>(_spShapeComponent);
		return m_spWorldOBB->Intersects(*spOBBComponent->GetOBB());
	}

	default:
		CHECKF(false, L"The shader type is not designated.");
		break;
	}
	return false;
}
