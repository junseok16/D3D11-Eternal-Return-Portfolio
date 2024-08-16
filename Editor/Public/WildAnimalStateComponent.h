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
		// 게임 매니저
		std::weak_ptr<CGameManager> m_wpGameManager;

		// 야생 동물
		std::weak_ptr<CWildAnimal> m_wpWildAnimal;

		// 생존자
		std::weak_ptr<CSurvivor> m_wpSurvivor;

	protected:
		// 낮밤 타입
		EDayType m_eDayType = EDayType::DAY;

		// 현재 야생 동물 상태
		EWildAnimalState m_eWildAnimalState = EWildAnimalState::ENUM_END;

		// 야생 동물의 습성
		EWildAnimalHabitType m_eWildAnimalHabitType = EWildAnimalHabitType::ENUM_END;

	protected:
		// 최대 추적 시간
		float m_fMaxChaseSeconds = 5.0f;

		// 누적 추적 시간
		float m_fSumChaseSeconds = 0.0f;

		// 이동한 메멘토들
		std::vector<Vector3> m_vecMementos;

		// 현재 메멘토 시간
		float m_fSumMementoSeconds = 0.0f;

		// 최대 메멘토 시간
		float m_fMaxMementoSeconds = 0.3f;

		// 공격 횟수
		int32 m_iSumSAttack = 0;

		int32 m_iMaxAttack = 3;
    };
}
