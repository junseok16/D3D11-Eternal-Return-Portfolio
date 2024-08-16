#pragma once
#include "StateComponent.h"

namespace Editor
{
	class CGameManager;
	class CSurvivor;
    class CWildAnimal;

    class CWildAnimalStateComponent : public CStateComponent
    {
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CWildAnimalStateComponent() = default;

		virtual ~CWildAnimalStateComponent() = default;

	/********************
		Events
	********************/
	public:
		virtual HRESULT PreInitializeComponent();

		virtual HRESULT InitializeComponent();

		virtual HRESULT PostInitializeComponent();

		virtual HRESULT BeginPlay();

		virtual int32 PreTickComponent(float _fDeltaSeconds);

		virtual int32 TickComponent(float _fDeltaSeconds);

		virtual int32 PostTickComponent(float _fDeltaSeconds);

		virtual HRESULT EndPlay();

		virtual void Render();

		virtual void Release();
		
	/********************
		Methods
	********************/
	public:
		// sleep
		bool IsSleepBeginEnterCondition();
		bool IsSleepBeginExitCondition();

		bool IsSleepEnterCondition();
		bool IsSleepExitCondition();

		// wake
		bool IsWakeEnterCondition();
		bool IsWakeExitCondition();

		// wait
		bool IsWaitEnterCondition();
		bool IsWaitExitCondition();

		// beware
		bool IsBewareBeginEnterCondition();
		bool IsBewareBeginExitCondition();

		bool IsBewareEnterCondition();
		bool IsBewareExitCondition();

		bool IsBewareEndEnterCondition();
		bool IsBewareEndExitCondition();

		// run
		bool IsRunEnterCondition();
		bool IsRunExitCondition();

		// skill
		bool IsSkillBeginEnterCondition();
		bool IsSkillBeginExitCondition();

		bool IsSkillEnterCondition();
		bool IsSkillExitCondition();

		// attack
		bool IsFirstAttackEnterCondition();
		bool IsFirstAttackExitCondition();

		bool IsSecondAttackEnterCondition();
		bool IsSecondAttackExitCondition();

		// end battle
		bool IsEndBattleEnterCondition();
		bool IsEndBattleExitCondition();

		// death
		bool IsDeathEnterCondition();
		bool IsDeathExitCondition();

		// appear
		bool IsAppearEnterCondition();
		bool IsAppearExitCondition();

		// dance
		bool IsDanceEnterCondition();
		bool IsDanceExitCondition();
		
	public:
		virtual void UpdateWildAnimalState(float _fDeltaSeconds);

		virtual void UpdateWildAnimalBehavior(float _fDeltaSeconds);
		
	/********************
		Overrides
	********************/
	public:
		virtual void OnAnimEnter(uint32 _iAnimState, float _fRatio) override;

		virtual void OnAnimStay(uint32 _iAnimState, float _fRatio) override;

		virtual void OnAnimExit(uint32 _iAnimState, float _fRatio) override;
		
	/********************
		Getter/Setter
	********************/
	public:
		void SetWildAnimalState(EWildAnimalState _eWildAnimalState) { m_eWildAnimalState = _eWildAnimalState; }

		EWildAnimalState GetWildAnimalState() const { return m_eWildAnimalState; }

	/********************
		Data Members
	********************/
	protected:
		// ���� �Ŵ���
		std::weak_ptr<CGameManager> m_wpGameManager;

		// �߻� ����
		std::weak_ptr<CWildAnimal> m_wpWildAnimal;

		// ������
		std::weak_ptr<CSurvivor> m_wpSurvivor;

	protected:
		// ���� Ÿ��
		EDayType m_eDayType = EDayType::DAY;

		// ���� �߻� ���� ����
		EWildAnimalState m_eWildAnimalState = EWildAnimalState::ENUM_END;

		// �߻� ������ ����
		EWildAnimalHabitType m_eWildAnimalHabitType = EWildAnimalHabitType::ENUM_END;

	protected:
		// �ִ� ���� �ð�
		float m_fMaxChaseSeconds = 5.0f;

		// ���� ���� �ð�
		float m_fSumChaseSeconds = 0.0f;

		// �̵��� �޸����
		std::vector<Vector3> m_vecMementos;

		// ���� �޸��� �ð�
		float m_fSumMementoSeconds = 0.0f;

		// �ִ� �޸��� �ð�
		float m_fMaxMementoSeconds = 0.3f;

		// ���� Ƚ��
		int32 m_iSumSAttack = 0;

		int32 m_iMaxAttack = 3;
    };
}
