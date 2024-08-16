#pragma once
#include "PrimitiveComponent.h"

namespace Engine
{
	class CCameraManager;

	class ENGINE_DLL CShapeComponent : public CPrimitiveComponent
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CShapeComponent() = default;

		virtual ~CShapeComponent() = default;

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
		Methods
	********************/
	public:
		virtual bool IsCollided(const std::shared_ptr<CShapeComponent>& _spShapeComponent) abstract;

		virtual bool IsCollisionFlagIntersect(const std::shared_ptr<CShapeComponent> _spShapeComponent);

		void ResetCollisionFalg() { m_iCollisionFlag = 0x0000'0000; }

		void AddCollisionFlag(ECollisionLayer _eCollisionLayer);

		void RemoveCollisionFlag(ECollisionLayer _eCollisionLayer);
		
	/********************
		Getter/Setter
	********************/
	public:
		void SetCollided(bool _bCollided) { m_bCollided = _bCollided; }

		bool IsCollided() const { return m_bCollided; }

		EShapeType GetShapeType() const { return m_eShapeType; }

		void SetCollisionLayer(ECollisionLayer _eCollisionLayer) { m_eCollisionLayer = _eCollisionLayer; }

		ECollisionLayer GetCollisionLayer() const { return m_eCollisionLayer; }

		std::unordered_set<std::shared_ptr<CShapeComponent>>& GetShapeComponents() { return m_usetShapeComponents; }

		void SetActive(bool _bActive) { m_bActive = _bActive; }

		bool IsActive() const { return m_bActive; }

	/********************
		Data Members
	********************/
	protected:
		std::shared_ptr<PrimitiveBatch<VertexPositionColor>> m_spPrimitiveBatch = nullptr;

		std::shared_ptr<BasicEffect> m_spBasicEffect = nullptr;

		ComPtr<ID3D11InputLayout> m_cpInputLayout = nullptr;
		
		ComPtr<ID3D11Device> m_cpDevice = nullptr;
		
		ComPtr<ID3D11DeviceContext> m_cpDeviceContext = nullptr;

	protected:
		// 충돌 활성화 여부
		bool m_bActive = true;

		// 다른 콜라이더와 충돌했는지 여부
		bool m_bCollided = false;

		// 콜라이더의 모양
		EShapeType m_eShapeType = EShapeType::ENUM_END;

		// 콜리전 레이어
		ECollisionLayer m_eCollisionLayer = ECollisionLayer::ENUM_END;

		// 콜리전 플래그
		uint32 m_iCollisionFlag = 0x0000'0000;

		// 이 셰이프 컴포넌트와 충돌한 다른 셰이프 컴포넌트들
		std::unordered_set<std::shared_ptr<CShapeComponent>> m_usetShapeComponents;
	};
}
