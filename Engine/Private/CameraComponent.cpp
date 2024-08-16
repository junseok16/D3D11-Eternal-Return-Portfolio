// default
#include "pch.h"
#include "CameraComponent.h"

// module
#include "EngineModule.h"

// manager
#include "CameraManager.h"
#include "InputManager.h"

// actor
#include "Actor.h"

// world
#include "World.h"

#include "MathUtility.h"

HRESULT Engine::CCameraComponent::PreInitializeComponent()
{
	if (FAILED(CSceneComponent::PreInitializeComponent())) { return E_FAIL; }
	m_wpInputManager = CWorld::GetInstance()->GetEngineModule()->GetInputManager();
	CHECK(!m_wpCameraManager.expired());
	CHECK(!m_wpInputManager.expired());

	return S_OK;
}

HRESULT Engine::CCameraComponent::InitializeComponent()
{
	if (FAILED(CSceneComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CCameraComponent::PostInitializeComponent()
{
	if (FAILED(CSceneComponent::PostInitializeComponent())) { return E_FAIL; }

	m_fCurAzimuthRadian = XMConvertToRadians(180.0f);
	m_fCurElevationRadian = XMConvertToRadians(15.0f);
	return S_OK;
}

HRESULT Engine::CCameraComponent::BeginPlay()
{
	if (FAILED(CSceneComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CCameraComponent::PreTickComponent(float _fDeltaSeconds)
{
	if (m_bCameraWalk)
	{
		PlayCameraWalk(_fDeltaSeconds);
		return 0;
	}

	if (!m_wpOwnerActor.lock()->IsOnAir()) { return 0; }

	if (m_bCameraLocked) { return 0; }

	if (m_fLerpFOVDelay > 0.0f)
	{
		m_fSumLerpFOVDelay += _fDeltaSeconds;

		if (m_fSumLerpFOVDelay >= m_fLerpFOVDelay)
		{
			m_fSumLerpFOVDelay = 0.0f;
			m_fLerpFOVDelay = 0.0f;
			m_bLerpFOV = true;
		}
	}

	if (m_bLerpFOV)
	{
		LerpFOV(_fDeltaSeconds);
	}

	if (m_bLerpCameraOffset)
	{
		LerpCameraOffset(_fDeltaSeconds);
	}

	if (m_bLerpRadius)
	{
		LerpRadius(_fDeltaSeconds);
	}

	if (m_eCameraType == ECameraType::THIRD_PERSON)
	{
		if (m_bSavePreRadian)
		{
			m_fCurAzimuthRadian = m_fPreAzimuthRadian;
			m_fCurElevationRadian = m_fPreElevationRadian;
			m_bSavePreRadian = false;
		}

		// 방위각을 갱신합니다.
		if (int32 iDeltaX = m_wpInputManager.lock()->GetMouseDelta(EMouseAxisType::X_AXIS))
		{
			m_fCurAzimuthRadian += XMConvertToRadians(iDeltaX * m_fSensitivity * _fDeltaSeconds);
			m_fCurAzimuthRadian = std::clamp(m_fCurAzimuthRadian, XMConvertToRadians(m_fMinAzimuthDegree), XMConvertToRadians(m_fMaxAzimuthDegree));
		}

		// 앙각을 갱신합니다.
		if (int32 iDeltaY = m_wpInputManager.lock()->GetMouseDelta(EMouseAxisType::Y_AXIS))
		{
			m_fCurElevationRadian += XMConvertToRadians(iDeltaY * m_fSensitivity * _fDeltaSeconds);
			m_fCurElevationRadian = std::clamp(m_fCurElevationRadian, XMConvertToRadians(m_fMinElevationDegree), XMConvertToRadians(m_fMaxElevationDegree));
		}
	}
	else if (m_eCameraType == ECameraType::FIRST_PERSON)
	{
		if (int32 iDeltaX = m_wpInputManager.lock()->GetMouseDelta(EMouseAxisType::X_AXIS))
		{
			Vector3 vScale = Vector3::One;
			Vector3 vRotate = Vector3::Zero;
			Vector3 vTranslate = Vector3::Zero;
			Quaternion qtnRotate;
		
			{
				Matrix matWorld = m_wpOwnerActor.lock()->GetActorWorldMatrix().value();
				matWorld.Decompose(vScale, qtnRotate, vTranslate);
				vRotate = qtnRotate.ToEuler();

				float fPreDegree = XMConvertToDegrees(vRotate.y);
				float fDegree = iDeltaX * m_fSensitivity * _fDeltaSeconds;
				m_wpOwnerActor.lock()->SetActorLocalRotate(Vector3::Up, fPreDegree + fDegree);
			}
		}

		/*
		if (!m_bSavePreRadian)
		{
			m_fPreAzimuthRadian = m_fCurAzimuthRadian;
			m_fPreElevationRadian = m_fCurElevationRadian;
			m_bSavePreRadian = true;

			m_fCurAzimuthRadian = 180.0f;
		}

		// 방위각을 갱신합니다.
		if (int32 iDeltaX = m_wpInputManager.lock()->GetMouseDelta(EMouseAxisType::X_AXIS))
		{
			Vector3 vScale = Vector3::One;
			Vector3 vRotate = Vector3::Zero;
			Vector3 vTranslate = Vector3::Zero;
			Quaternion qtnRotate;
		
			{
				Matrix matWorld = m_wpOwnerActor.lock()->GetActorWorldMatrix().value();
				matWorld.Decompose(vScale, qtnRotate, vTranslate);
				vRotate = qtnRotate.ToEuler();

				float fPreDegree = XMConvertToDegrees(vRotate.y);
				float fDegree = iDeltaX * m_fSensitivity * _fDeltaSeconds;
				m_wpOwnerActor.lock()->SetActorLocalRotate(Vector3::Up, fPreDegree + fDegree);
			}
		}
		m_fCurElevationRadian = 0.0f;

		*/
	}

	/*
	// 카메라 중심을 갱신합니다.
	m_vCenter = m_wpOwnerActor.lock()->GetActorWorldPosition().value() + m_vCurCameraOffset;

	// 카메라의 포워드 벡터를 갱신합니다.
	m_vCameraCartesian = m_vCenter + RecalcCartesian();
	m_vCameraForward = m_vCenter - m_vCameraCartesian;
	m_vCameraForward.Normalize();

	// 카메라의 라이트 벡터를 구합니다.
	m_vCameraRight = Vector3::Up.Cross(m_vCameraForward);
	m_vCameraRight.Normalize();
	*/
	return 0;
}

int32 Engine::CCameraComponent::TickComponent(float _fDeltaSeconds)
{
	if (!m_wpOwnerActor.lock()->IsOnAir()) { return 0; }

	return 0;
}

int32 Engine::CCameraComponent::PostTickComponent(float _fDeltaSeconds)
{
	if (!m_wpOwnerActor.lock()->IsOnAir()) { return 0; }

	return 0;
}

HRESULT Engine::CCameraComponent::EndPlay()
{
	if (FAILED(CSceneComponent::EndPlay())) { return E_FAIL; }
	return S_OK;
}

void Engine::CCameraComponent::Render()
{
	CSceneComponent::Render();
}

void Engine::CCameraComponent::Release()
{
	CSceneComponent::Release();
}

void Engine::CCameraComponent::SetThisCameraOnAir()
{
	m_wpCameraManager = CWorld::GetInstance()->GetEngineModule()->GetCameraManager();
	m_wpCameraManager.lock()->SetCurCamera(m_wpOwnerActor.lock()->GetActorName());
}

void Engine::CCameraComponent::LerpCameraOffset(float _fDeltaSeconds)
{
	m_fSumLerpCameraOffsetSeconds += _fDeltaSeconds;

	float fRatio = CMathUtility::GetSquaredLerpSeconds(4, m_fSumLerpCameraOffsetSeconds, m_fMaxLerpCameraOffsetSeconds);
	if (m_fSumLerpCameraOffsetSeconds >= m_fMaxLerpCameraOffsetSeconds)
	{
		fRatio = 1.0f;
		m_fSumLerpCameraOffsetSeconds = 0.0f;
		m_bLerpCameraOffset = false;
	}

	m_vCurCameraOffset = Vector3::Lerp(m_vFromCameraOffset, m_vToCameraOffset, fRatio);
}

void Engine::CCameraComponent::LerpRadius(float _fDeltaSeconds)
{
	m_fSumLerpRadiusSeconds += _fDeltaSeconds;

	float fRatio = CMathUtility::GetSquaredLerpSeconds(4, m_fSumLerpRadiusSeconds, m_fMaxLerpRadiusSeconds);
	if (m_fSumLerpRadiusSeconds >= m_fMaxLerpRadiusSeconds)
	{
		fRatio = 1.0f;
		m_fSumLerpRadiusSeconds = 0.0f;
		m_bLerpRadius = false;
	}

	m_fCurRadius = lerp(m_fFromRadius, m_fToRadius, fRatio);
}

void Engine::CCameraComponent::LerpFOV(float _fDeltaSeconds)
{
	m_fSumLerpFOVSeconds += _fDeltaSeconds;

	float fRatio = 0.0f;
	if (m_bLinearLerp)
	{
		fRatio = m_fSumLerpFOVSeconds / m_fMaxLerpFOVSeconds;
	}
	else
	{
		fRatio = CMathUtility::GetSquaredLerpSeconds(4, m_fSumLerpFOVSeconds, m_fMaxLerpFOVSeconds);
	}

	if (m_fSumLerpFOVSeconds >= m_fMaxLerpFOVSeconds)
	{
		fRatio = 1.0f;
		m_fSumLerpFOVSeconds = 0.0f;
		m_bLerpFOV = false;
	}

	m_fCurFieldOfView = lerp(m_fFromFieldOfView, m_fToFieldOfView, fRatio);
}

void Engine::CCameraComponent::SetDelayLerpFOVTo(float _fToFOV, float _fDelaySeonds, float _fMaxLerpSeconds, bool _bLinear)
{
	m_fSumLerpFOVDelay = 0.0f;
	m_fLerpFOVDelay = _fDelaySeonds;
	m_fFromFieldOfView = m_fCurFieldOfView;
	m_fToFieldOfView = _fToFOV;
	m_bLinearLerp = _bLinear;
}

void Engine::CCameraComponent::SetLerpFOVTo(float _fToFOV, float _fMaxLerpSeconds)
{
	m_fFromFieldOfView = m_fCurFieldOfView;
	m_fToFieldOfView = _fToFOV;
	m_bLerpFOV = true;
}

void Engine::CCameraComponent::SetLerpCameraOffsetTo(const Vector3& _vToCameraOffset, float _fMaxLerpSeconds)
{
	m_vFromCameraOffset = m_vCurCameraOffset;
	m_vToCameraOffset = _vToCameraOffset;
	m_bLerpCameraOffset = true;
}

void Engine::CCameraComponent::SetLerpRadiusTo(float _fToRadius, float _fMaxLerpSeconds)
{
	m_fFromRadius = m_fCurRadius;
	m_fToRadius = _fToRadius;
	m_bLerpRadius = true;
}

void Engine::CCameraComponent::PlayCameraWalk(float _fDeltaSeconds)
{
	m_fLerpCameraWalkDeltaSeconds += _fDeltaSeconds;

	if (5.0f <= m_fLerpCameraWalkDeltaSeconds)
	{
		m_fLerpCameraWalkDeltaSeconds = 0.0f;
		m_bCameraWalk = false;
		m_bCameraWalkFinished = true;
		return;
	}

	m_fCurAzimuthRadian = XMConvertToRadians(lerp(90.0f, -155.0f, m_fLerpCameraWalkDeltaSeconds / 5.0f));
	m_vCurCameraOffset.y = lerp(0.5f, 2.0f, m_fLerpCameraWalkDeltaSeconds / 5.0f);
	m_fCurRadius = lerp(3.0f, 2.0f, m_fLerpCameraWalkDeltaSeconds / 5.0f);
	m_fCurElevationRadian = 0.0f;
}

Vector3 Engine::CCameraComponent::RecalcCartesian()
{
	float fX = m_fCurRadius * cosf(m_fCurElevationRadian) * sinf(m_fCurAzimuthRadian);
	float fY = m_fCurRadius * sinf(m_fCurElevationRadian);
	float fZ = m_fCurRadius * cosf(m_fCurElevationRadian) * cosf(m_fCurAzimuthRadian);
	return Vector3(fX, fY, fZ);
}

void Engine::CCameraComponent::RecalcCameraMatrix()
{
	if (m_eCameraType == ECameraType::FIRST_PERSON)
	{
		m_vCameraForward = m_wpOwnerActor.lock()->GetActorWorldForwardVector().value();
		m_vCameraForward.Normalize();

		m_vCameraRight = m_wpOwnerActor.lock()->GetActorWorldRightVector().value();
		m_vCameraRight.Normalize();

		Vector3 vUp = Vector3::Up;

		Vector3 vCameraPosition = m_wpOwnerActor.lock()->GetActorWorldPosition().value() + 0.8f * m_vCameraRight + 1.4f * vUp - 1.5f * m_vCameraForward;

		// 뷰 행렬을 구합니다.
		m_matView = XMMatrixLookToLH(vCameraPosition, m_vCameraForward, Vector3::Up);

		// 원근 투영 행렬을 구합니다.
		m_matPerspectiveProjection = XMMatrixPerspectiveFovLH(XMConvertToRadians(m_fCurFieldOfView), m_fAspectRatio, m_fNearPlane, m_fFarPlane);

		// 직교 투영 행렬을 구합니다.
		m_matOrthogonalProjection = XMMatrixOrthographicLH(1280.0f, 720.0f, 0.1f, 1000.0f);
		return;
	}

	// 카메라 중심을 갱신합니다.
	m_vCenter = m_wpOwnerActor.lock()->GetActorWorldPosition().value() + m_vCurCameraOffset;

	// 카메라의 포워드 벡터를 갱신합니다.
	m_vCameraCartesian = m_vCenter + RecalcCartesian();
	m_vCameraForward = m_vCenter - m_vCameraCartesian;
	m_vCameraForward.Normalize();

	// 카메라의 라이트 벡터를 구합니다.
	m_vCameraRight = Vector3::Up.Cross(m_vCameraForward);
	m_vCameraRight.Normalize();

	// 뷰 행렬을 구합니다.
	m_matView = XMMatrixLookToLH(m_vCameraCartesian, m_vCameraForward, Vector3::Up);
	
	// 원근 투영 행렬을 구합니다.
	m_matPerspectiveProjection = XMMatrixPerspectiveFovLH(XMConvertToRadians(m_fCurFieldOfView), m_fAspectRatio, m_fNearPlane, m_fFarPlane);
	
	// 직교 투영 행렬을 구합니다.
	m_matOrthogonalProjection = XMMatrixOrthographicLH(1280.0f, 720.0f, 0.1f, 1000.0f);
}
