// default
#include "pch.h"
#include "Actor.h"

// component
#include "SceneComponent.h"
#include "CameraComponent.h"
#include "SphereComponent.h"
#include "AABBComponent.h"
#include "OBBComponent.h"
#include "LightComponent.h"
#include "EffectComponent.h"

// manager
#include "CameraManager.h"
#include "CollisionManager.h"
#include "LightManager.h"
#include "EffectManager.h"

// world
#include "World.h"

// module
#include "EngineModule.h"

HRESULT Engine::CActor::PreInitialize()
{
	return S_OK;
}

HRESULT Engine::CActor::Initialize()
{
	for (const auto& pair : m_umapActorComponents)
	{
		if (FAILED(pair.second->PreInitializeComponent())) { return E_FAIL; }
	}

	for (const auto& pair : m_umapActorComponents)
	{
		if (FAILED(pair.second->InitializeComponent())) { return E_FAIL; }
	}

	for (const auto& pair : m_umapActorComponents)
	{
		if (FAILED(pair.second->PostInitializeComponent())) { return E_FAIL; }
	}

	return S_OK;
}

HRESULT Engine::CActor::PostInitialize()
{
	return S_OK;
}

HRESULT Engine::CActor::BeginPlay()
{
	for (const auto& pair : m_umapActorComponents)
	{
		if (FAILED(pair.second->BeginPlay())) { return E_FAIL; }
	}

	return S_OK;
}

int32 Engine::CActor::PreTick(float _fDeltaSeconds)
{
	for (const auto& pair : m_umapActorComponents)
	{
		switch (pair.second->PreTickComponent(_fDeltaSeconds))
		{
		case 0:		continue;
		case -1:	return -1;
		default:	break;
		}
	}
	return 0;
}

int32 Engine::CActor::Tick(float _fDeltaSeconds)
{
	for (const auto& pair : m_umapActorComponents)
	{
		switch (pair.second->TickComponent(_fDeltaSeconds))
		{
		case 0:		continue;
		case -1:	return -1;
		default:	break;
		}
	}
	return 0;
}

int32 Engine::CActor::PostTick(float _fDeltaSeconds)
{
	for (const auto& pair : m_umapActorComponents)
	{
		switch (pair.second->PostTickComponent(_fDeltaSeconds))
		{
		case 0:		continue;
		case -1:	return -1;
		default:	break;
		}
	}
	return 0;
}

HRESULT Engine::CActor::EndPlay()
{
	for (const auto& pair : m_umapActorComponents)
	{
		if (FAILED(pair.second->EndPlay())) { return E_FAIL; }
	}

	return S_OK;
}

void Engine::CActor::Render()
{
	for (const auto& pair : m_umapActorComponents)
	{
		if (pair.second->GetComponentType() != EComponentType::EFFECT)
		{
			pair.second->Render();
		}
	}
}

void Engine::CActor::RenderShadow()
{
	for (const auto& pair : m_umapActorComponents)
	{
		switch (pair.second->GetComponentType())
		{
		case EComponentType::SKELETAL_MESH:
		// case EComponentType::STATIC_MESH:
			pair.second->RenderShadow();
			break;

		default:
			break;
		}
	}
}

void Engine::CActor::Release()
{
	for (auto& pair : m_umapActorComponents)
	{
		pair.second->Release();
		pair.second = nullptr;
	}
	m_umapActorComponents.clear();
}

const std::shared_ptr<CSceneComponent> Engine::CActor::GetRootComponent() const
{
	return m_wpRootComponent.expired() ? nullptr : m_wpRootComponent.lock();
}

const std::optional<Vector3> Engine::CActor::GetActorWorldForwardVector() const
{
	if (!m_wpRootComponent.expired())
	{
		return m_wpRootComponent.lock()->GetWorldForwardVector();
	}
	return nullopt;
}

const std::optional<Vector3> Engine::CActor::GetActorWorldUpVector() const
{
	if (!m_wpRootComponent.expired())
	{
		return m_wpRootComponent.lock()->GetWorldUpVector();
	}
	return nullopt;
}

const std::optional<Vector3> Engine::CActor::GetActorWorldRightVector() const
{
	if (!m_wpRootComponent.expired())
	{
		return m_wpRootComponent.lock()->GetWorldRightVector();
	}
	return nullopt;
}

const std::optional<Matrix> Engine::CActor::GetActorWorldMatrix() const
{
	if (!m_wpRootComponent.expired())
	{
		return m_wpRootComponent.lock()->GetComponentWorldMatrix();
	}
	return nullopt;
}

const optional<Vector3> Engine::CActor::GetActorLocalPosition() const
{
	if (!m_wpRootComponent.expired())
	{
		return m_wpRootComponent.lock()->GetComponentLocalPosition();
	}
	return nullopt;
}

const optional<Vector3> Engine::CActor::GetActorWorldScale() const
{
	if (!m_wpRootComponent.expired())
	{
		return m_wpRootComponent.lock()->GetComponentWorldScale();
	}
	return nullopt;
}

std::shared_ptr<CPawn> Engine::CActor::GetInstigatorPawn() const
{
	return m_wpInstigatorPawn.expired() ? nullptr : m_wpInstigatorPawn.lock();
}

const std::shared_ptr<CWorld> Engine::CActor::GetOwnerWorld() const
{
	return m_wpOwnerWorld.expired() ? nullptr : m_wpOwnerWorld.lock();
}

const std::shared_ptr<CLevel> Engine::CActor::GetOwnerLevel() const
{
	return m_wpOwnerLevel.expired() ? nullptr : m_wpOwnerLevel.lock();
}

const std::shared_ptr<CActor> Engine::CActor::GetOwnerActor() const
{
	return m_wpOwnerActor.expired() ? nullptr : m_wpOwnerActor.lock();
}

void Engine::CActor::SetRootComponent(const std::shared_ptr<CSceneComponent> _spSceneComponent)
{
	if (!m_wpRootComponent.expired())
	{
		m_wpRootComponent.lock()->SetRootComponent(false);
	}
	m_wpRootComponent = _spSceneComponent;
	_spSceneComponent->SetRootComponent(true);
}

void Engine::CActor::SetActorLocalPosition(const Vector3& _vLocalPosition)
{
	if (m_wpRootComponent.expired()) { CHECKF(false, L"Root component is not designated."); }
	m_wpRootComponent.lock()->SetComponentLocalPosition(_vLocalPosition);
}

void Engine::CActor::SetActorLocalScale(const Vector3& _vLocalScale)
{
	if (m_wpRootComponent.expired()) { CHECKF(false, L"Root component is not designated."); return; }
	m_wpRootComponent.lock()->SetComponentLocalScale(_vLocalScale);
}

void Engine::CActor::SetActorLocalRotate(const Vector3& _vAxis, float _fDegree)
{
	if (m_wpRootComponent.expired()) { CHECKF(false, L"Root component is not designated."); return; }
	m_wpRootComponent.lock()->SetComponentLocalRotate(_vAxis, _fDegree);
}

void Engine::CActor::SetActorLocalMatrix(const Matrix& _matLocal)
{
	if (m_wpRootComponent.expired()) { CHECKF(false, L"Root component is not designated."); return; }
	m_wpRootComponent.lock()->SetComponentLocalMatrix(_matLocal);
}

const std::optional<Vector3> Engine::CActor::GetActorWorldPosition() const
{
	if (!m_wpRootComponent.expired())
	{
		return m_wpRootComponent.lock()->GetComponentWorldPosition();
	}
	return nullopt;
}

const std::optional<Vector3> Engine::CActor::GetActorLocalScale() const
{
	if (!m_wpRootComponent.expired())
	{
		return m_wpRootComponent.lock()->GetComponentLocalScale();
	}
	return nullopt;
}

void Engine::CActor::SetActorTransform(ETransformType _eTransformType, Vector4 _vTransform)
{
	if (m_wpRootComponent.expired()) { return; }
	
	m_wpRootComponent.lock()->SetLocalTransform(_eTransformType, _vTransform);
}

void Engine::CActor::SetSocketMatrix(const Matrix& _matSocket)
{
	if (m_wpRootComponent.expired()) { return; }

	m_wpRootComponent.lock()->SetSocketMatrix(_matSocket);
}

bool Engine::CActor::HasComponent(EComponentType _eComponentType) const
{
	return m_ummapComponentTypes.find(_eComponentType) != m_ummapComponentTypes.end();
}

bool Engine::CActor::IsInFrustum(float _fRadius)
{
	if (m_wpRootComponent.expired()) { return false; }

	return m_wpRootComponent.lock()->IsInFrustum(_fRadius);
}

bool Engine::CActor::IsInFrustum(const Vector4& _vWorldPosition, float _fRadius)
{
	if (m_wpRootComponent.expired()) { return false; }

	return m_wpRootComponent.lock()->IsInFrustum(_vWorldPosition, _fRadius);
}

void Engine::CActor::LookAt(const Vector3& _vPoint)
{
	Vector3 vScale = GetActorLocalScale().value();
	Vector3 vPosition = GetActorLocalPosition().value();

	Vector3 vForward = _vPoint - vPosition;
	Vector3 vRight = XMVector3Cross(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), vForward);
	Vector3 vUp = XMVector3Cross(vForward, vRight);

	SetActorTransform(ETransformType::RIGHT,	XMVector3Normalize(vRight)	* vScale.x);
	SetActorTransform(ETransformType::UP,		XMVector3Normalize(vUp)		* vScale.y);
	SetActorTransform(ETransformType::FORWARD,	XMVector3Normalize(vForward)* vScale.z);
}

float Engine::CActor::TakeDamage(float _fDamageAmount, std::shared_ptr<CController> _spInstigatorController, std::shared_ptr<CPawn> _spInstigatorPawn)
{
	return 0.0f;
}

void Engine::CActor::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	return;
}

void Engine::CActor::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	return;
}

void Engine::CActor::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	return;
}

void Engine::CActor::OnAnimEnter(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	return;
}

void Engine::CActor::OnAnimStay(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	return;
}

void Engine::CActor::OnAnimExit(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	return;
}

void Engine::CActor::AddActorComponent(const std::wstring& _wstrActorComponentName, EComponentType _eComponentType, std::shared_ptr<CActorComponent> _spActorComponent)
{
	m_umapActorComponents.emplace(_wstrActorComponentName, _spActorComponent);
	m_ummapComponentTypes.emplace(_eComponentType, _wstrActorComponentName);
}

bool Engine::CActor::RemoveActorComponent(const std::wstring& _wstrActorComponentName, EComponentType _eComponentType)
{
	if (m_umapActorComponents.find(_wstrActorComponentName) == m_umapActorComponents.end()) { return false; }

	// TODO; 에디터에서 삭제하는 경우, 전부 해제하면 안 됩니다.
	m_umapActorComponents[_wstrActorComponentName]->Release();
	m_umapActorComponents[_wstrActorComponentName] = nullptr;
	m_umapActorComponents.erase(_wstrActorComponentName);

	auto pair = m_ummapComponentTypes.equal_range(_eComponentType);
	for (auto iter = pair.first; iter != pair.second; ++iter)
	{
		if (iter->second == _wstrActorComponentName)
		{
			m_ummapComponentTypes.erase(iter);
			break;
		}
	}
	return true;
}

void Engine::CActor::AddToManager(const std::wstring& _wstrActorComponentName, EComponentType _eComponentType, std::shared_ptr<CActorComponent> _spActorComponent)
{
	shared_ptr<CEngineModule> spEngineModule = CWorld::GetInstance()->GetEngineModule();

	switch (_eComponentType)
	{
	// 카메라 컴포넌트
	case Engine::EComponentType::CAMERA:
	{
		shared_ptr<CCameraManager> spCameraManager = spEngineModule->GetCameraManager();
		spCameraManager->AddCameraComponent(m_wstrActorName, dynamic_pointer_cast<CCameraComponent>(_spActorComponent));
	}
	break;

	// 콜라이더 컴포넌트
	case Engine::EComponentType::SPHERE:
	case Engine::EComponentType::AABB:
	case Engine::EComponentType::OBB:
	{
		shared_ptr<CCollisionManager> spCollisionManager = spEngineModule->GetCollisionManager();
		spCollisionManager->AddShapeComponent(dynamic_pointer_cast<CShapeComponent>(_spActorComponent));
	}
	break;

	case Engine::EComponentType::EFFECT:
	{
		shared_ptr<CEffectManager> spEffectManager = spEngineModule->GetEffectManager();
		spEffectManager->AddEffectComponent(_wstrActorComponentName, dynamic_pointer_cast<CEffectComponent>(_spActorComponent));
	}
	break;

	// 라이트 컴포넌트
	case Engine::EComponentType::DIRECTIONAL_LIGHT:
	{
		shared_ptr<CLightManager> spLightManager = spEngineModule->GetLightManager();
		spLightManager->AddLightComponent(_wstrActorComponentName, dynamic_pointer_cast<CLightComponent>(_spActorComponent), ELightType::DIRECTIONAL);
	}
	break;

	case Engine::EComponentType::POINT_LIGHT:
	{
		shared_ptr<CLightManager> spLightManager = spEngineModule->GetLightManager();
		spLightManager->AddLightComponent(_wstrActorComponentName, dynamic_pointer_cast<CLightComponent>(_spActorComponent), ELightType::POINT);
	}
	break;

	case Engine::EComponentType::SPOT_LIGHT:
	{
		shared_ptr<CLightManager> spLightManager = spEngineModule->GetLightManager();
		spLightManager->AddLightComponent(_wstrActorComponentName, dynamic_pointer_cast<CLightComponent>(_spActorComponent), ELightType::SPOT);
	}
	break;

	default:
		break;
	}
}

void Engine::CActor::RemoveFromManager(const std::wstring& _wstrActorComponentName, EComponentType _eComponentType)
{
	shared_ptr<CEngineModule> spEngineModule = CWorld::GetInstance()->GetEngineModule();

	switch (_eComponentType)
	{
	// 카메라 컴포넌트
	case Engine::EComponentType::CAMERA:
	{
		shared_ptr<CCameraManager> spCameraManager = spEngineModule->GetCameraManager();
		spCameraManager->RemoveCameraComponent(m_wstrActorName);
	}
	break;

	// 콜라이더 컴포넌트
	case Engine::EComponentType::SPHERE:
	case Engine::EComponentType::AABB:
	case Engine::EComponentType::OBB:
	{
		shared_ptr<CCollisionManager> spCollisionManager = spEngineModule->GetCollisionManager();
	}
	break;

	// 라이트 컴포넌트
	case Engine::EComponentType::DIRECTIONAL_LIGHT:
	case Engine::EComponentType::POINT_LIGHT:
	case Engine::EComponentType::SPOT_LIGHT:
		break;

	default:
		break;
	}
}
