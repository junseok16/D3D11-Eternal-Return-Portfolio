// default
#include "pch.h"
#include "CameraManager.h"

// component
#include "CameraComponent.h"

#include "Frustum.h"

HRESULT Engine::CCameraManager::PreInitialize()
{
	m_spFrustum = CFrustum::Create();
	m_spFrustum->SetCameraManager(dynamic_pointer_cast<CCameraManager>(shared_from_this()));
	return S_OK;
}

HRESULT Engine::CCameraManager::Initialize()
{
	return S_OK;
}

int32 Engine::CCameraManager::Tick()
{
	if (m_wpCurCameraComponent.expired()) { return 0; }

	m_spFrustum->Tick();

	m_wpCurCameraComponent.lock()->RecalcCameraMatrix();
	m_matCurView = m_wpCurCameraComponent.lock()->GetViewMatrix();
	m_matCurPerspectiveProjection = m_wpCurCameraComponent.lock()->GetPerspectiveProjectionMatrix();
	m_matCurOrthogonalProjection = m_wpCurCameraComponent.lock()->GetOrthogonalProjectionMatrix();
	return 0;
}

void Engine::CCameraManager::Release()
{
	m_spFrustum = nullptr;
}

HRESULT Engine::CCameraManager::SetCurCamera(const std::wstring& _wstrCameraName)
{
	if (m_umapCameraComponents.find(_wstrCameraName) == m_umapCameraComponents.end()) { return E_FAIL; }

	m_wpCurCameraComponent = m_umapCameraComponents[_wstrCameraName];
	return S_OK;
}

Vector3 Engine::CCameraManager::GetCurCameraPosition() const
{
	Matrix matWorld = m_matCurView.Invert();
	return matWorld.Translation();
}

Vector3 Engine::CCameraManager::GetCurCameraForward() const
{
	Matrix matWorld = m_matCurView.Invert();
	Vector3 vForward = -matWorld.Forward();
	vForward.Normalize();
	return vForward;
}

HRESULT Engine::CCameraManager::AddCameraComponent(const std::wstring& _wstrCameraName, const std::shared_ptr<CCameraComponent>& _spCameraComponent)
{
	if (m_umapCameraComponents.find(_wstrCameraName) != m_umapCameraComponents.end()) { return E_FAIL; }
	
	m_umapCameraComponents.emplace(_wstrCameraName, _spCameraComponent);
	return S_OK;
}

HRESULT Engine::CCameraManager::RemoveCameraComponent(const std::wstring& _wstrCameraComponentName)
{
	if (m_umapCameraComponents.find(_wstrCameraComponentName) == m_umapCameraComponents.end()) { return E_FAIL; }

	m_umapCameraComponents.erase(_wstrCameraComponentName);
	return S_OK;
}

bool Engine::CCameraManager::IsInFrustum(const Vector4& _vWorldPosition, float _fRadius)
{
	return m_spFrustum->IsInFrustum(_vWorldPosition, _fRadius);
}
