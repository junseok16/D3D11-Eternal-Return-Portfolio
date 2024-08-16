#include "pch.h"
#include "EditorCamera.h"

#include "EngineModule.h"

#include "CameraManager.h"
#include "InputManager.h"

std::shared_ptr<CEditorCamera> Editor::CEditorCamera::Create(const std::shared_ptr<CEngineModule>& _spEngineModule)
{
	const shared_ptr<CEditorCamera> spEditorCamera = make_shared<CEditorCamera>();
	spEditorCamera->Initialize(_spEngineModule);
	return spEditorCamera;
}

HRESULT Editor::CEditorCamera::Initialize(const std::shared_ptr<CEngineModule>& _spEngineModule)
{
	m_wpCameraManager = _spEngineModule->GetCameraManager();
	m_wpInputManager = _spEngineModule->GetInputManager();
	return S_OK;
}

int32 Editor::CEditorCamera::Tick(float _fDeltaSeconds)
{
	if (m_bOnAir)
	{
		return 0;
	}

	TickFocus();
	if (m_bFocus)
	{
		TickInput(_fDeltaSeconds);
	}

	TickTransform(_fDeltaSeconds);
	TickCamera(_fDeltaSeconds);
	return 0;
}

void Editor::CEditorCamera::Release()
{
}

void Editor::CEditorCamera::TickFocus()
{
	if (m_wpInputManager.lock()->IsKeyDown(DIK_F8))
	{
		m_bFocus = !m_bFocus;
	}
}

void Editor::CEditorCamera::TickInput(float _fDeltaSeconds)
{
	if (m_wpInputManager.lock()->IsKeyPressed(DIK_W))
	{
		Vector3 vLocalPosition = GetLocalPosition();
		vLocalPosition += GetForwardVector() * m_fSpeed * _fDeltaSeconds;
		SetLocalPosition(vLocalPosition);
	}

	if (m_wpInputManager.lock()->IsKeyPressed(DIK_S))
	{
		Vector3 vLocalPosition = GetLocalPosition();
		vLocalPosition -= GetForwardVector() * m_fSpeed * _fDeltaSeconds;
		SetLocalPosition(vLocalPosition);
	}

	if (m_wpInputManager.lock()->IsKeyPressed(DIK_D))
	{
		Vector3 vLocalPosition = GetLocalPosition();
		vLocalPosition += GetRightVector() * m_fSpeed * _fDeltaSeconds;
		SetLocalPosition(vLocalPosition);
	}

	if (m_wpInputManager.lock()->IsKeyPressed(DIK_A))
	{
		Vector3 vLocalPosition = GetLocalPosition();
		vLocalPosition -= GetRightVector() * m_fSpeed * _fDeltaSeconds;
		SetLocalPosition(vLocalPosition);
	}

	if (m_wpInputManager.lock()->IsKeyPressed(DIK_E))
	{
		Vector3 vLocalPosition = GetLocalPosition();
		vLocalPosition += GetUpVector() * m_fSpeed * _fDeltaSeconds;
		SetLocalPosition(vLocalPosition);
	}

	if (m_wpInputManager.lock()->IsKeyPressed(DIK_Q))
	{
		Vector3 vLocalPosition = GetLocalPosition();
		vLocalPosition -= GetUpVector() * m_fSpeed * _fDeltaSeconds;
		SetLocalPosition(vLocalPosition);
	}

	if (m_wpInputManager.lock()->IsKeyPressed(DIK_PGUP))
	{
		m_fSpeed += 10.0f;

		if (m_fSpeed >= 100.0f) { m_fSpeed = 100.0f; }
	}

	if (m_wpInputManager.lock()->IsKeyPressed(DIK_PGDN))
	{
		m_fSpeed -= 10.0f;

		if (m_fSpeed <= 0.0f) { m_fSpeed = 10.0f; }
	}

	if (int32 iDeltaX = m_wpInputManager.lock()->GetMouseDelta(EMouseAxisType::X_AXIS))
	{
		Matrix matRotateMatrix;
		matRotateMatrix = matRotateMatrix.CreateFromAxisAngle(Vector3::Up, XMConvertToRadians(iDeltaX / 10.0f));
		m_matMouseRotate *= matRotateMatrix;
	}

	if (int32 iDeltaY = m_wpInputManager.lock()->GetMouseDelta(EMouseAxisType::Y_AXIS))
	{
		Matrix matRotateMatrix;
		matRotateMatrix = matRotateMatrix.CreateFromAxisAngle(GetRightVector(), XMConvertToRadians(iDeltaY / 10.0f));
		m_matMouseRotate *= matRotateMatrix;
	}
}

void Editor::CEditorCamera::TickTransform(float _fDeltaSeconds)
{
	m_matLocal = m_matWorld = Matrix::Identity;
	m_matLocal *= Matrix::CreateScale(m_vLocalScale);
	m_matLocal *= Matrix::CreateRotationX(XMConvertToRadians(m_vLocalRotate.x));
	m_matLocal *= Matrix::CreateRotationY(XMConvertToRadians(m_vLocalRotate.y));
	m_matLocal *= Matrix::CreateRotationZ(XMConvertToRadians(m_vLocalRotate.z));
	m_matLocal *= m_matMouseRotate;
	m_matLocal *= Matrix::CreateTranslation(m_vLocalTranslate);

	// 월드 행렬을 구합니다.
	m_matWorld = m_matLocal;

	// 월드 행렬에서 각 성분을 구합니다.
	m_matWorld.Decompose(m_vWorldScale, m_qtWorldRotate, m_vWorldTranslate);
	m_vWorldRotate = m_qtWorldRotate.ToEuler();
}

void Editor::CEditorCamera::TickCamera(float _fDeltaSeconds)
{
	// 뷰 행렬을 구합니다.
	m_matView = XMMatrixLookToLH(m_vWorldTranslate, GetForwardVector(), Vector3::Up);
	m_wpCameraManager.lock()->SetCurViewMatrix(m_matView);

	// 원근 투영 행렬을 구합니다.
	m_matPerspectiveProjection = XMMatrixPerspectiveFovLH(XMConvertToRadians(m_fFieldOfView), m_fAspectRatio, m_fNearPlane, m_fFarPlane);
	m_wpCameraManager.lock()->SetCurPerspectiveProjectionMatrix(m_matPerspectiveProjection);

	// 직교 투영 행렬을 구합니다.
	m_matOrthogonalProjection = XMMatrixOrthographicLH(1280.0f, 720.0f, 0.1f, 1000.0f);
	m_wpCameraManager.lock()->SetCurOrthogonalProjectionMatrix(m_matOrthogonalProjection);
}
