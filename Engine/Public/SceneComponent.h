#pragma once
#include "ActorComponent.h"

namespace Engine
{
	class CCameraManager;

	class ENGINE_DLL CSceneComponent : public CActorComponent
	{
		enum : uint8
		{
			RIGHT,
			UP,
			FORWARD,
			POSITION,
			ENUM_END
		};
		
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CSceneComponent() = default;

		virtual ~CSceneComponent() = default;

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
		void SetComponentLocalScale(const Vector3& _vScale);

		void SetComponentLocalPosition(const Vector3& _vTranlate);

		void SetComponentLocalRotate(const Vector3& _vAxis, float _fDegree);

		void SetComponentLocalMatrix(const Matrix& _matLocal);

		Vector3 GetComponentLocalScale();

		Vector3 GetComponentLocalPosition();

		Vector3 GetComponentWorldScale();

		Vector3 GetComponentWorldPosition();

	public:
		void SetLocalTransform(ETransformType _eTransformType, Vector4 _vTransform);

		Vector4 GetLocalTransform(ETransformType _eTransformType) const;

		Vector4 GetWorldTransform(ETransformType _eTransformType) const;

	public:
		const Matrix& GetComponentWorldMatrix() const { return m_matWorld; }

		const Vector3 GetWorldRightVector() const { return m_matWorld.Right(); }

		const Vector3 GetWorldUpVector() const { return m_matWorld.Up(); }

		const Vector3 GetWorldForwardVector() const { return -m_matWorld.Forward(); };

		// �Ҽ�
		const std::shared_ptr<CSceneComponent> GetOwnerComponent() const;

		void SetOwnerComponent(const std::shared_ptr<CSceneComponent> _spOwnerComponent) { m_wpOwnerComponent = _spOwnerComponent; }

		bool IsRootComponent() const { return m_bRootComponent; }

		void SetRootComponent(bool _bRootComponent) { m_bRootComponent = _bRootComponent; }
		
		void SetSocketMatrix(const Matrix& _matSocket) { m_matSocket = _matSocket; }
		
	/********************
		Getter/Setter
	********************/
	public:
		bool IsInFrustum(float _fRadius);

		bool IsInFrustum(const Vector4& _vWorldPosition, float _fRadius);

	/********************
		Data Members
	********************/
	protected:
		// ���� ���
		Matrix m_matLocal = Matrix::Identity;

		// ���� ���
		Matrix m_matSocket = Matrix::Identity;

		// ���� ���
		Matrix m_matWorld = Matrix::Identity;

	protected:
		// ��Ʈ ������Ʈ���� ����
		bool m_bRootComponent = false;

		// �� ������Ʈ�� ���� �ִ� �� ������Ʈ
		std::weak_ptr<CSceneComponent> m_wpOwnerComponent;

	protected:
		std::weak_ptr<CCameraManager> m_wpCameraManager;
	};
}
