#include "pch.h"
#include "AABBComponent.h"

// manager
#include "CameraManager.h"

// actor
#include "Actor.h"

// component
#include "SphereComponent.h"
#include "OBBComponent.h"

HRESULT Engine::CAABBComponent::PreInitializeComponent()
{
	if (FAILED(CShapeComponent::PreInitializeComponent())) { return E_FAIL; }
	m_spLocalAABB = make_shared<BoundingBox>();
	m_spWorldAABB = make_shared<BoundingBox>();

	m_spLocalAABB->Center = m_spWorldAABB->Center = Vector3::Zero;
	m_spLocalAABB->Extents = m_spWorldAABB->Extents = Vector3::One;
	m_eShapeType = EShapeType::AABB;
	return S_OK;
}

HRESULT Engine::CAABBComponent::InitializeComponent()
{
	if (FAILED(CShapeComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CAABBComponent::PostInitializeComponent()
{
	if (FAILED(CShapeComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CAABBComponent::BeginPlay()
{
	if (FAILED(CShapeComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CAABBComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CShapeComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CAABBComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CShapeComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	XMMATRIX matWorld = m_wpOwnerActor.lock()->GetActorWorldMatrix().value();

	matWorld.r[0] = Vector4::UnitX * XMVector3Length(matWorld.r[0]).m128_f32[0];
	matWorld.r[1] = Vector4::UnitY * XMVector3Length(matWorld.r[1]).m128_f32[0];
	matWorld.r[2] = Vector4::UnitZ * XMVector3Length(matWorld.r[2]).m128_f32[0];

	m_spLocalAABB->Transform(*m_spWorldAABB, matWorld);
	return 0;
}

int32 Engine::CAABBComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CShapeComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Engine::CAABBComponent::EndPlay()
{
	if (FAILED(CShapeComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CAABBComponent::Render()
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

	DX::Draw(m_spPrimitiveBatch.get(), *m_spWorldAABB, m_bCollided ? Colors::Red : Colors::Green);

	m_spPrimitiveBatch->End();
	
#endif
*/
	CShapeComponent::Render();
}

void Engine::CAABBComponent::Release()
{
	m_spLocalAABB = nullptr;
	m_spWorldAABB = nullptr;
	CShapeComponent::Release();
}

bool Engine::CAABBComponent::IsCollided(const std::shared_ptr<CShapeComponent>& _spShapeComponent)
{
	if (IsCollisionFlagIntersect(_spShapeComponent) == false) { return false; }

	switch (_spShapeComponent->GetShapeType())
	{
	case EShapeType::SPHERE:
	{
		shared_ptr<CSphereComponent> spSphereComponent = static_pointer_cast<CSphereComponent>(_spShapeComponent);
		return m_spWorldAABB->Intersects(*spSphereComponent->GetSphere());
	}

	case EShapeType::AABB:
	{
		shared_ptr<CAABBComponent> spAABBComponent = static_pointer_cast<CAABBComponent>(_spShapeComponent);
		return m_spWorldAABB->Intersects(*spAABBComponent->GetAABB());
	}

	case EShapeType::OBB:
	{
		shared_ptr<COBBComponent> spOBBComponent = static_pointer_cast<COBBComponent>(_spShapeComponent);
		return m_spWorldAABB->Intersects(*spOBBComponent->GetOBB());
	}

	default:
		CHECKF(false, L"The shader type is not designated.");
		break;
	}
	return false;
}
