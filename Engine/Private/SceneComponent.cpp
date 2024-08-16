// default
#include "pch.h"
#include "SceneComponent.h"

// actor
#include "Actor.h"

#include "World.h"
#include "EngineModule.h"

#include "CameraManager.h"

HRESULT Engine::CSceneComponent::PreInitializeComponent()
{
	if (FAILED(CActorComponent::PreInitializeComponent())) { return E_FAIL; }

	m_wpCameraManager = CWorld::GetInstance()->GetEngineModule()->GetCameraManager();
	CHECK(!m_wpCameraManager.expired());
	return S_OK;
}

HRESULT Engine::CSceneComponent::InitializeComponent()
{
	if (FAILED(CActorComponent::InitializeComponent())) { return E_FAIL; }
	return S_OK;
}

HRESULT Engine::CSceneComponent::PostInitializeComponent()
{
	if (FAILED(CActorComponent::PostInitializeComponent())) { return E_FAIL; }
	return S_OK;
}

HRESULT Engine::CSceneComponent::BeginPlay()
{
	if (FAILED(CActorComponent::BeginPlay())) { return E_FAIL; }
	return S_OK;
}

int32 Engine::CSceneComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CActorComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CSceneComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CActorComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	// 루트 컴포넌트인 경우, 즉 액터와 트랜스폼이 같은 경우
	if (m_bRootComponent)
	{
		const shared_ptr<CActor>& spActor = CActorComponent::GetOwnerActor()->CActor::GetOwnerActor();
		if (spActor) { m_matWorld = m_matLocal * m_matSocket * spActor->GetRootComponent()->GetComponentWorldMatrix(); }
		else
		{
			m_matWorld = m_matLocal;
		}
	}
	// 루트 컴포넌트가 아닌 경우
	else
	{
		CHECK(!m_wpOwnerComponent.expired());

		// 이 컴포넌트를 갖고 있는 컴포넌트의 월드 행렬을 곱합니다.
		m_matWorld = m_matLocal * m_wpOwnerComponent.lock()->GetComponentWorldMatrix();
	}

	return 0;
}

int32 Engine::CSceneComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CActorComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Engine::CSceneComponent::EndPlay()
{
	if (FAILED(CActorComponent::EndPlay())) { return E_FAIL; }
	return S_OK;
}

void Engine::CSceneComponent::Render()
{
	CActorComponent::Render();
}

void Engine::CSceneComponent::Release()
{
	CActorComponent::Release();
}

void Engine::CSceneComponent::SetComponentLocalScale(const Vector3& _vScale)
{
	SetLocalTransform(ETransformType::RIGHT,	XMVector3Normalize(GetLocalTransform(ETransformType::RIGHT))	* _vScale.x);
	SetLocalTransform(ETransformType::UP,		XMVector3Normalize(GetLocalTransform(ETransformType::UP))		* _vScale.y);
	SetLocalTransform(ETransformType::FORWARD,	XMVector3Normalize(GetLocalTransform(ETransformType::FORWARD))	* _vScale.z);
}

void Engine::CSceneComponent::SetComponentLocalPosition(const Vector3& _vTranlate)
{
	Vector4 v4Translate = { _vTranlate.x, _vTranlate.y, _vTranlate.z, 1.0f };
	SetLocalTransform(ETransformType::POSITION, v4Translate);
}

void Engine::CSceneComponent::SetComponentLocalRotate(const Vector3& _vAxis, float _fDegree)
{
	Vector4 v4Axis = { _vAxis.x, _vAxis.y, _vAxis.z, 0.0f };

	Matrix matRotate = XMMatrixRotationAxis(v4Axis, XMConvertToRadians(_fDegree));
	Vector3 vScale = GetComponentLocalScale();

	for (size_t iIndex = 0; iIndex < 3; ++iIndex)
	{
		Vector4 vTemp = Vector4::Zero;

		*((float*)&vTemp + iIndex) = 1.0f * *((float*)&vScale + iIndex);

		SetLocalTransform(static_cast<ETransformType>(iIndex), XMVector4Transform(vTemp, matRotate));
	}
}

void Engine::CSceneComponent::SetComponentLocalMatrix(const Matrix& _matLocal)
{
	m_matLocal = _matLocal;
}

Vector3 Engine::CSceneComponent::GetComponentLocalScale()
{
	return Vector3
	(
		XMVector3Length(GetLocalTransform(ETransformType::RIGHT)).m128_f32[0],
		XMVector3Length(GetLocalTransform(ETransformType::UP)).m128_f32[0],
		XMVector3Length(GetLocalTransform(ETransformType::FORWARD)).m128_f32[0]
	);
}

Vector3 Engine::CSceneComponent::GetComponentLocalPosition()
{
	return m_matLocal.Translation();
}

Vector3 Engine::CSceneComponent::GetComponentWorldScale()
{
	return Vector3
	(
		XMVector3Length(GetWorldTransform(ETransformType::RIGHT)).m128_f32[0],
		XMVector3Length(GetWorldTransform(ETransformType::UP)).m128_f32[0],
		XMVector3Length(GetWorldTransform(ETransformType::FORWARD)).m128_f32[0]
	);
}

Vector3 Engine::CSceneComponent::GetComponentWorldPosition()
{
	return m_matWorld.Translation();
}

const std::shared_ptr<CSceneComponent> Engine::CSceneComponent::GetOwnerComponent() const
{
	if (m_bRootComponent) { return nullptr; }

	return m_wpOwnerComponent.expired() ? nullptr : m_wpOwnerComponent.lock();
}

bool Engine::CSceneComponent::IsInFrustum(float _fRadius)
{
	Vector4 vWorldPosition = GetLocalTransform(ETransformType::POSITION);
	return m_wpCameraManager.lock()->IsInFrustum(vWorldPosition, _fRadius);
}

bool Engine::CSceneComponent::IsInFrustum(const Vector4& _vWorldPosition, float _fRadius)
{
	return m_wpCameraManager.lock()->IsInFrustum(_vWorldPosition, _fRadius);
}

void Engine::CSceneComponent::SetLocalTransform(ETransformType _eTransformType, Vector4 _vTransform)
{
	memcpy(&m_matLocal.m[(int32)_eTransformType], &_vTransform, sizeof(Vector4));
}

Vector4 Engine::CSceneComponent::GetLocalTransform(ETransformType _eTransformType) const
{
	Vector4 vTemp = Vector4::Zero;
	memcpy(&vTemp, &m_matLocal.m[(int32)_eTransformType], sizeof(Vector4));
	return vTemp;
}

Vector4 Engine::CSceneComponent::GetWorldTransform(ETransformType _eTransformType) const
{
	Vector4 vTemp = Vector4::Zero;
	memcpy(&vTemp, &m_matWorld.m[(int32)_eTransformType], sizeof(Vector4));
	return vTemp;
}
