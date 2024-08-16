#pragma once
#include "SceneComponent.h"

namespace Engine
{
	class CInputManager;
	class CCameraManager;

	class ENGINE_DLL CCameraComponent : public CSceneComponent
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CCameraComponent() = default;

		virtual ~CCameraComponent() = default;

	/********************
		Events
	********************/
	public:
		virtual HRESULT PreInitializeComponent() override;

		virtual HRESULT InitializeComponent() override;

		virtual HRESULT PostInitializeComponent() override;

		virtual HRESULT BeginPlay() override;

		virtual int32 PreTickComponent(float _fDeltaSeconds) override;

		virtual int32 TickComponent(float _fDeltaSeconds) override;

		virtual int32 PostTickComponent(float _fDeltaSeconds) override;

		virtual HRESULT EndPlay() override;

		virtual void Render() override;

		virtual void Release() override;

	/********************
		Getter/Setter
	********************/
	public:
		void SetAspectRatio(float _fAspectRatio) { m_fAspectRatio = _fAspectRatio; };

		void SetFieldOfView(float _fFieldOfView) { m_fCurFieldOfView = _fFieldOfView; }

		float GetFieldOfView() { return m_fCurFieldOfView; }

		void SetFarPlane(float _fFarPlane) { m_fFarPlane = _fFarPlane; }

		void SetNearPlane(float _fNearPlane) { m_fNearPlane = _fNearPlane; }

		void SetProjectionType(EProjectionType _eProjectionType) { m_eProjectionType = _eProjectionType; }

		void SetCameraType(ECameraType _eCameraType) { m_eCameraType = _eCameraType; }

		ECameraType GetCameraType() const { return m_eCameraType; }

		void SetThisCameraOnAir();

	public:
		void SetCurCameraCenter(const Vector3& _vCenter) { m_vCenter = _vCenter; }

		const Vector3& GetCurCameraCenter() const { return m_vCenter; }

		const Matrix& GetViewMatrix() const { return m_matView; }

		const Matrix& GetPerspectiveProjectionMatrix() const { return m_matPerspectiveProjection; }

		const Matrix& GetOrthogonalProjectionMatrix() const { return m_matOrthogonalProjection; }

		const Vector3& GetCameraForwardVector() const { return m_vCameraForward; }

		const Vector3& GetCameraRightVector() const { return m_vCameraRight; }

		std::shared_ptr<CCameraManager> GetCameraManager() const { return m_wpCameraManager.expired() ? nullptr : m_wpCameraManager.lock(); }
		
	public:
		void SetOffset(const Vector3 _vCameraOffset) { m_vCurCameraOffset = _vCameraOffset; }

		void SetRadius(float _fRadius) { m_fCurRadius = _fRadius; }

		float GetRadius() const { return m_fCurRadius; }

		float GetCurAzimuthRadian() const { return m_fCurAzimuthRadian; }

		float GetCurElevationRadian() const { return m_fCurElevationRadian; }

		void SetCurAzimuthRadian(float _fAzimuthRadian) { m_fCurAzimuthRadian = _fAzimuthRadian; }

		void SetCurElevationRadian(float _fElevationRadian) { m_fCurElevationRadian = _fElevationRadian; }

		void SetSensitivity(float _fSensitivity) { m_fSensitivity = _fSensitivity; }

		float GetSensitivity() const { return m_fSensitivity; }

		void LockCamera(bool _bCameraLocked) { m_bCameraLocked = _bCameraLocked; }

	private:
		void LerpCameraOffset(float _fDeltaSeconds);

		void LerpRadius(float _fDeltaSeconds);

		void LerpFOV(float _fDeltaSeconds);

	public:
		void SetDelayLerpFOVTo(float _fToFOV, float _fDelaySeonds, float _fMaxLerpSeconds, bool _bLinear = false);
		
		void SetLerpFOVTo(float _fToFOV, float _fMaxLerpSeconds = 1.0f);

		void SetLerpCameraOffsetTo(const Vector3& _vToCameraOffset, float _fMaxLerpSeconds = 1.0f);

		void SetLerpRadiusTo(float _fToRadius, float _fMaxLerpSeconds = 1.0f);

		void SetShoulderView(bool _bShoulderViwe) { m_bShoulderView = _bShoulderViwe; }

	public:
		void SetCameraWalk(bool _bCameraWalk) { m_bCameraWalk = _bCameraWalk; }

		void PlayCameraWalk(float _fDeltaSeconds);

		bool IsCameraWalkFinished() const { return m_bCameraWalkFinished; }

		bool m_bCameraWalk = false;

		bool m_bCameraWalkFinished = false;

		float m_fLerpCameraWalkDeltaSeconds = 0.0f;

	/********************
		Methods
	********************/
	private:
		Vector3 RecalcCartesian();

	public:
		void RecalcCameraMatrix();

	/********************
		Data Members
	********************/
	private:
		bool m_bLinearLerp = false;

		bool m_bLerpCameraOffset = false;

		bool m_bLerpRadius = false;

		bool m_bLerpFOV = false;

		float m_fSumLerpCameraOffsetSeconds = 0.0f;

		float m_fSumLerpRadiusSeconds = 0.0f;

		float m_fSumLerpFOVSeconds = 0.0f;

		float m_fMaxLerpCameraOffsetSeconds = 1.0f;

		float m_fMaxLerpRadiusSeconds = 1.0f;

		float m_fMaxLerpFOVSeconds = 1.0f;

		// 이전 카메라 FOV
		float m_fFromFieldOfView = 60.0f;

		// 현재 카메라 FOV
		float m_fCurFieldOfView = 60.0f;

		// 이후 카메라 FOV
		float m_fToFieldOfView = 60.0f;

		// 이전 카메라 오프셋
		Vector3 m_vFromCameraOffset = Vector3::Zero;

		// 이후 카메라 오프셋
		Vector3 m_vToCameraOffset = Vector3::Zero;

		// 현재 카메라 오프셋
		Vector3 m_vCurCameraOffset = Vector3::Zero;

		// 이전 구의 반지름
		float m_fFromRadius = 5.0f;

		// 이후 구의 반지름
		float m_fToRadius = 5.0f;

		// 현재 구의 반지름
		float m_fCurRadius = 5.0f;

		float m_fLerpFOVDelay = 0.0f;

		float m_fSumLerpFOVDelay = 0.0f;

		ECameraType m_eCameraType = ECameraType::THIRD_PERSON;

	private:
		// 카메라 위치
		Vector3 m_vCameraCartesian = Vector3::Zero;

		// 구의 중심
		Vector3 m_vCenter = Vector3::Zero;

		// 마우스 감도
		float m_fSensitivity = 3.0f;

		// 방위각
		float m_fCurAzimuthRadian = 0.0f;

		// 최소 방위각
		float m_fMinAzimuthDegree = -360.0f;

		// 최대 방위각
		float m_fMaxAzimuthDegree = 360.0f;

		// 앙각
		float m_fCurElevationRadian = 0.0f;

		// 최소 앙각
		float m_fMinElevationDegree = 5.0f;

		// 최대 앙각
		float m_fMaxElevationDegree = 60.0f;

		float m_fSumRadian = 0.0f;

	private:
		Matrix m_matView = Matrix::Identity;

		Matrix m_matPerspectiveProjection = Matrix::Identity;

		Matrix m_matOrthogonalProjection = Matrix::Identity;

	private:
		bool m_bCameraLocked = false;

		float m_fAspectRatio = 16.0f / 9.0f;

		float m_fFarPlane = 1'000.0f;

		float m_fNearPlane = 1.0f;

		EProjectionType m_eProjectionType = EProjectionType::ENUM_END;
	
		Vector3 m_vCameraForward = Vector3::UnitZ;

		Vector3 m_vCameraRight = Vector3::UnitX;

		bool m_bShoulderView = false;

		bool m_bSavePreRadian = false;

		float m_fPreAzimuthRadian = 0.0f;

		float m_fPreElevationRadian = 0.0f;

	private:
		std::weak_ptr<CInputManager> m_wpInputManager;
	};
}
