#pragma once
#include "StateComponent.h"

namespace Client
{
	class CGameManager;
	class CSurvivor;
	class CBoss;

	class CBossStateComponent : public CStateComponent
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CBossStateComponent() = default;

		virtual ~CBossStateComponent() = default;
		
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
		// wait
		bool IsWaitEnterCondition();
		bool IsWaitExitCondition();

		// run
		bool IsRunEnterCondition();
		bool IsRunExitCondition();

		// skill 01 (위클라인: 순간 이동)
		bool IsFirstSkillBeginEnterCondition();
		bool IsFirstSkillBeginExitCondition();

		bool IsFirstSkillEnterCondition();
		bool IsFirstSkillExitCondition();

		bool IsFirstSkillEndEnterCondition();
		bool IsFirstSkillEndExitCondition();

		// skill 02 (위클라인: 중독 직선 발사)
		bool IsSecondSkillBeginEnterCondition();
		bool IsSecondSkillBeginExitCondition();

		bool IsSecondSkillEnterCondition();
		bool IsSecondSkillExitCondition();

		bool IsSecondSkillEndEnterCondition();
		bool IsSecondSkillEndExitCondition();

		// skill 03 (위클라인: 중독 공 여러 개 던지기, WAIT 애니메이션 활용)
		bool IsThirdSkillBeginEnterCondition();
		bool IsThirdSkillBeginExitCondition();

		bool IsThirdSkillEnterCondition();
		bool IsThirdSkillExitCondition();

		bool IsThirdSkillEndEnterCondition();
		bool IsThirdSkillEndExitCondition();

		// skill 04 (위클라인:
		/*
		bool IsFourthSkillBeginEnterCondition();
		bool IsFourthSkillBeginExitCondition();

		bool IsFourthSkillEnterCondition();
		bool IsFourthSkillExitCondition();

		bool IsFourthSkillEndEnterCondition();
		bool IsFourthSkillEndExitCondition();
		*/

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

	public:
		virtual void UpdateBossState(float _fDeltaSeconds);

		virtual void UpdateBossBehavior(float _fDeltaSeconds);
		
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
		void SetBossState(EBossState _eBossState) { m_eBossState = _eBossState; }

		EBossState GetBossState() const { return m_eBossState; }
		
	/********************
		Data Members
	********************/
	protected:
		// 게임 매니저
		std::weak_ptr<CGameManager> m_wpGameManager;

		// 생존자
		std::weak_ptr<CSurvivor> m_wpSurvivor;

		// 보스
		std::weak_ptr<CBoss> m_wpBoss;

	protected:
		// 보스 상태
		EBossState m_eBossState = EBossState::ENUM_END;

		// 최대 추적 시간
		float m_fMaxChaseSeconds = 5.0f;

		// 누적 추적 시간
		float m_fSumChaseSeconds = 0.0f;

		// 최대 배회 시간
		float m_fMaxWanderSeconds = 10.0f;

		// 누적 배회 시간
		float m_fSumWanderSeconds = 0.0f;

		// 최대 대기 시간
		float m_fMaxWaitSeconds = 2.0f;

		// 누적 대기 시간
		float m_fSumWaitSeconds = 0.0f;

		// 최대 공격 횟수
		int32 m_iMaxAttack = 4;

		// 누적 공격 횟수
		int32 m_iSumAttack = 0;
	};
}
