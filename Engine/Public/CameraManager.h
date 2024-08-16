#pragma once
#include "Manager.h"

namespace Engine
{
	class CFrustum;
	class CCameraComponent;

	class ENGINE_DLL CCameraManager : public Engine::CManager
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CCameraManager() = default;

		virtual ~CCameraManager() = default;

	/********************
		Events
	********************/
	public:
		HRESULT PreInitialize();

		HRESULT Initialize();

		int32 Tick();

		virtual void Release() override;
		
	/********************
		Getter/Setter
	********************/
	public:
		void SetCurViewMatrix(const Matrix& _matCurView) { m_matCurView = _matCurView; }

		void SetCurPerspectiveProjectionMatrix(const Matrix& _matCurPerspectiveProjection) { m_matCurPerspectiveProjection = _matCurPerspectiveProjection; }
		
		void SetCurOrthogonalProjectionMatrix(const Matrix& _matCurOrthogonalProjection) { m_matCurOrthogonalProjection = _matCurOrthogonalProjection; }

		const Matrix& GetCurViewMatrix() const { return m_matCurView; }

		const Matrix& GetCurPerspectiveProjectionMatrix() const { return m_matCurPerspectiveProjection; }

		const Matrix& GetCurOrthogonalProjectionMatrix() const { return m_matCurOrthogonalProjection; }

	public:
		HRESULT SetCurCamera(const std::wstring& _wstrCameraComponentName);

		std::shared_ptr<CCameraComponent> GetCurCamera() const { return m_wpCurCameraComponent.expired() ? nullptr : m_wpCurCameraComponent.lock(); }

		Vector3 GetCurCameraPosition() const;

		Vector3 GetCurCameraForward() const;

	/********************
		Methods
	********************/
	public:
		HRESULT AddCameraComponent(const std::wstring& _wstrCameraComponentName, const std::shared_ptr<CCameraComponent>& _spCameraComponent);

		HRESULT RemoveCameraComponent(const std::wstring& _wstrCameraComponentName);

		bool IsInFrustum(const Vector4& _vWorldPosition, float _fRadius);

	/********************
		Data Members
	********************/
	private:
		// ī�޶� ������Ʈ��
		std::unordered_map<std::wstring, std::weak_ptr<CCameraComponent>> m_umapCameraComponents;

		// ���� ī�޶� ������Ʈ
		std::weak_ptr<CCameraComponent> m_wpCurCameraComponent;

	private:
		// ���� �� ���
		Matrix m_matCurView = Matrix::Identity;

		// ���� ���� ���� ���
		Matrix m_matCurPerspectiveProjection = Matrix::Identity;

		// ���� ���� ���� ���
		Matrix m_matCurOrthogonalProjection = Matrix::Identity;

	private:
		std::shared_ptr<CFrustum> m_spFrustum = nullptr;
	};
}
