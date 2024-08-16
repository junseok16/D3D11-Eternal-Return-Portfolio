#pragma once
#include "Character.h"

namespace Engine
{
	class CSphereComponent;
	class CNavigationComponent;
}

namespace Editor
{
	class CInGamePanel;
	class CBossStateComponent;

	class CBoss : public CCharacter
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CBoss() = default;

		virtual ~CBoss() = default;
		
	/********************
		Events
	********************/
	public:
		virtual HRESULT PreInitialize() override;

		virtual HRESULT Initialize() override;

		virtual HRESULT PostInitialize() override;

		virtual HRESULT BeginPlay() override;

		virtual int32 PreTick(float _fDeltaSeconds) override;

		virtual int32 Tick(float _fDeltaSeconds) override;

		virtual int32 PostTick(float _fDeltaSeconds) override;

		virtual HRESULT EndPlay() override;

		virtual void Render() override;

		virtual void Release() override;
		
	/********************
		Methods
	********************/
	public:
		virtual void OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst) override;

		virtual void OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst) override;

		virtual void OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst) override;

		virtual float TakeDamage(float _fDamageAmount, std::shared_ptr<CController> _spInstigatorController, std::shared_ptr<CPawn> _spInstigatorPawn);

	/********************
		Getter/Setter
	********************/
	public:
		bool IsDead() const { return m_fCurHP <= 0.0f; }

		float GetCurHP() const { return m_fCurHP; }

		float GetCurSP() const { return m_fCurSP; }

		float GetMaxHP() const { return m_fMaxHP; }

		float GetMaxSP() const { return m_fMaxSP; }

		float GetHPRegeneration() const { return m_fHPRegeneration; }

		float GetSPRegeneration() const { return m_fSPRegeneration; }

		float GetAttackRange() const { return m_fAttackRange; }

		float GetBewareDistance() const { return m_fBewareDistance; }

		float GetCurMoveSpeed() const { return m_fCurMoveSpeed; }

		const Vector3& GetWanderDirection() const { return m_vWanderDirection; }

		void SetWanderDirection(const Vector3& _vWanderDirection) { m_vWanderDirection = _vWanderDirection; }

	public:
		bool IsAttacked() const { return m_bAttacked; }

		void SetAttacked(bool _bAttacked) { m_bAttacked = _bAttacked; }

	public:
		void SetBossState(EBossState _eBossState);

		EBossState GetBossState() const;

	public:
		std::shared_ptr<CNavigationComponent> GetNavigationComponent() const { return m_wpNavigationComponent.expired() ? nullptr : m_wpNavigationComponent.lock(); }

	/********************
		Data Members
	********************/
	protected:
		std::weak_ptr<CBossStateComponent> m_wpBossStateComponent;

		std::weak_ptr<CNavigationComponent> m_wpNavigationComponent;

		std::weak_ptr<CSphereComponent> m_wpBodySphereComponent;

	public:
		std::shared_ptr<CInGamePanel> m_spInGamePanel = nullptr;

	public:
		Vector3 m_vSpawnPosition = Vector3::Zero;

		int32 m_iSpawnCellIndex = -1;

	protected:
		float m_fCurHP = 500.0f;
		
		float m_fMaxHP = 500.0f;

		float m_fCurSP = 500.0f;

		float m_fMaxSP = 500.0f;

		float m_fHPRegeneration = 1.0f;

		float m_fSPRegeneration = 1.0f;

		float m_fAttackRange = 3.0f;

		float m_fAttackPower = 10.0f;

		float m_fDefensePower = 10.0f;

		float m_fCurMoveSpeed = 3.0f;

		float m_fMaxMoveSpeed = 50.0f;

		float m_fBewareDistance = 5.0f;

		EBossType m_eBossType = EBossType::ENUM_END;

		// 배회 방향
		Vector3 m_vWanderDirection = Vector3::UnitX;

	protected:
		bool m_bAttacked = false;
	};
}
