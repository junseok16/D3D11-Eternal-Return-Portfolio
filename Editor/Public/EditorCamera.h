#pragma once

namespace Engine
{
	class CEngineModule;
	class CCameraManager;
	class CInputManager;
}

namespace Editor
{
	class CEditorCamera final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CEditorCamera() = default;

		virtual ~CEditorCamera() = default;
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CEditorCamera> Create(const std::shared_ptr<CEngineModule>& _spEngineModule);

		HRESULT Initialize(const std::shared_ptr<CEngineModule>& _spEngineModule);

		int32 Tick(float _fDeltaSeconds);

		void Release();
		
	/********************
		Getter/Setter
	********************/
	public:
		void SetLocalScale(const Vector3 _vLocalScale) { m_vLocalScale = _vLocalScale; }

		void SetLocalRotation(const Vector3 _vLocalRotation) { m_vLocalRotate = _vLocalRotation; }

		void SetLocalPosition(const Vector3 _vLocalPosition) { m_vLocalTranslate = _vLocalPosition; }
		
		const Vector3& GetLocalPosition() const { return m_vLocalTranslate; }

		const Vector3& GetLocalRotation() const { return m_vLocalRotate; }

		const Vector3& GetLocalScale() const { return m_vLocalScale; }

		const Vector3 GetForwardVector() const { return -m_matWorld.Forward(); };

		const Vector3 GetUpVector() const { return m_matWorld.Up(); }

		const Vector3 GetRightVector() const { return m_matWorld.Right(); }
		
		void SetOnAir(bool _bOnAir) { m_bOnAir = _bOnAir; }

	public:
		const Matrix& GetViewMatrix() { return m_matView; }

		const Matrix& GetPerspectiveProjectionMatrix() { return m_matPerspectiveProjection; }

	/********************
		Methods
	********************/
	private:
		void TickFocus();

		void TickInput(float _fDeltaSeconds);

		void TickTransform(float _fDeltaSeconds);

		void TickCamera(float _fDeltaSeconds);
		
	/********************
		Data Members
	********************/
	private:
		// 로컬 이동
		Vector3 m_vLocalTranslate = Vector3::Zero;

		// 로컬 회전
		Vector3 m_vLocalRotate = Vector3::Zero;

		// 로컬 크기
		Vector3 m_vLocalScale = Vector3::One;

		// 마우스의 회전 행렬
		Matrix m_matMouseRotate{};

		// 로컬 행렬
		Matrix m_matLocal = Matrix::Identity;

		// 월드 이동
		Vector3 m_vWorldTranslate = Vector3::Zero;

		// 월드 쿼터니언 회전
		Quaternion m_qtWorldRotate{ 0.0f, 0.0f, 0.0f, 1.0f };

		// 월드 오일러 회전
		Vector3 m_vWorldRotate = Vector3::Zero;

		// 월드 크기
		Vector3 m_vWorldScale = Vector3::One;

		// 월드 행렬
		Matrix m_matWorld = Matrix::Identity;

	private:
		Matrix m_matView = Matrix::Identity;

		Matrix m_matPerspectiveProjection = Matrix::Identity;

		Matrix m_matOrthogonalProjection = Matrix::Identity;

	private:
		float m_fAspectRatio = 16.0f / 9.0f;

		float m_fFieldOfView = 60.0f;

		float m_fFarPlane = 1'000.0f;

		float m_fNearPlane = 1.0f;

		EProjectionType m_eProjectionType = EProjectionType::PERSPECTIVE;

		bool m_bFocus = true;

		bool m_bOnAir = false;

	private:
		float m_fSpeed = 30.0f;

		float m_fMouseSensitivity = 10.0f;

	private:
		std::weak_ptr<CCameraManager> m_wpCameraManager;

		std::weak_ptr<CInputManager> m_wpInputManager;
	};
}
