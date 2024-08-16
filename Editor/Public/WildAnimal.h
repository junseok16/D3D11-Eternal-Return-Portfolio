#pragma once
#include "Character.h"

namespace Engine
{
	class CSphereComponent;
	class CNavigationComponent;
	class CStateComponent;
	class COBBComponent;
}

namespace Editor
{
	class CItemBoxPanel;
	class CItem;

	class CWildAnimalStateComponent;

	class CWildAnimal : public CCharacter
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CWildAnimal() = default;

		virtual ~CWildAnimal() = default;
		
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
		Getter/Setter
	********************/
	public:
		bool IsDead() const { return m_fCurHP <= 0.0f; }

		void SetCurHP(float _fCurHp) { m_fCurHP = _fCurHp; }

		float GetCurHP() const { return m_fCurHP; }

		float GetMaxHP() const { return m_fMaxHP; }

		float GetAttackRange() const { return m_fAttackRange; }
		
		float GetCurMoveSpeed() const { return m_fCurMoveSpeed; }

		bool IsAttacked() const { return m_bAttacked; }

		void SetAttacked(bool _bAttacked) { m_bAttacked = _bAttacked; }

		float GetBewareDistance() const { return m_fBewareDistance; }

		EWildAnimalHabitType GetWildAnimalHabit() const { return m_eWildAnimalHabitType; }

		std::shared_ptr<CNavigationComponent> GetNavigationComponent() const { return m_wpNavigationComponent.lock(); }

	public:
		void SetSpawnCellIndex(int32 _iCellIndex) { m_iSpawnCellIndex = _iCellIndex; }

		int32 GetSpawnCellIndex() const { return m_iSpawnCellIndex; }

		void SetSpawnPosition(const Vector3& _vSpawnPosition) { m_vSpawnPosition = _vSpawnPosition; }

		const Vector3& GetSpawnPosition() const { return m_vSpawnPosition; }

		void SetSpawnYDegree(float _fYDegree) { m_fSpawnYDegree = _fYDegree; }

		float GetSpawnYDegree() const { return m_fSpawnYDegree; }

	/********************
		Methods
	********************/
	public:
		// Actor overrides
		virtual float TakeDamage(float _fDamageAmount, std::shared_ptr<CController> _spInstigatorController, std::shared_ptr<CPawn> _spInstigatorPawn);

	/********************
		Data Members
	********************/
	protected:
		std::weak_ptr<CWildAnimalStateComponent> m_wpWildAnimalStateComponent;

		std::weak_ptr<CNavigationComponent> m_wpNavigationComponent;

		std::weak_ptr<CSphereComponent> m_wpBodySphereComponent;

		std::weak_ptr<COBBComponent> m_wpSkillOBBComponent;

	protected:
		// 현재 델타 타임
		float m_fDeltaSeconds = 0.0f;

		bool m_bAttacked = false;

	protected:
		Vector3 m_vSpawnPosition = Vector3::Zero;

		int32 m_iSpawnCellIndex = -1;

		float m_fSpawnYDegree = 0.0f;

	protected:
		// 주행성, 야행성 여부
		EWildAnimalHabitType m_eWildAnimalHabitType = EWildAnimalHabitType::ENUM_END;

		float m_fCurHP = 100.0f;

		float m_fHPRegeneration = 10.0f;

		float m_fMaxHP = 100.0f;

		float m_fCurSP = 100.0f;

		float m_fSPRegeneration = 10.0f;

		float m_fMaxSP = 100.0f;

		float m_fAttackRange = 1.0f;

		float m_fAttackPower = 10.0f;

		float m_fDefensePower = 10.0f;

		float m_fCurMoveSpeed = 2.0f;

		float m_fMaxMoveSpeed = 50.0f;

		float m_fRespawnInterval = 60.0f;

		float m_fBewareDistance = 7.0f;
	
		float m_fExp = 20.0f;

	public:
		void SetItemBoxPanel(const std::shared_ptr<CItemBoxPanel>& _spItemBoxPanel) { m_wpItemBoxPanel = _spItemBoxPanel; }

		bool IsOpened() const { return m_bOpened; }

		bool IsFirstOpened() const { return m_bFirstOpened; }

	public:
		void OpenItemBox();

		void CloseItemBox();

	public:
		std::array<std::shared_ptr<CItem>, 8>& GetItems() { return m_arrItems; }

		void RemoveItem(EItemSlotType _eItemSlotType);

	protected:
		// 아이템 박스 패널
		std::weak_ptr<CItemBoxPanel> m_wpItemBoxPanel;

		// 아이템 박스가 열렸는지 여부
		bool m_bOpened = false;

		// 아이템 박스가 처음 열렸는지 여부
		bool m_bFirstOpened = true;

		// 이 아이템 상자에 있는 아이템들
		std::array<std::shared_ptr<CItem>, 8> m_arrItems{ nullptr };
	};
}
