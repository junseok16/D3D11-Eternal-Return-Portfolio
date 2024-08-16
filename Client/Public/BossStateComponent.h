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

		// skill 01 (��Ŭ����: ���� �̵�)
		bool IsFirstSkillBeginEnterCondition();
		bool IsFirstSkillBeginExitCondition();

		bool IsFirstSkillEnterCondition();
		bool IsFirstSkillExitCondition();

		bool IsFirstSkillEndEnterCondition();
		bool IsFirstSkillEndExitCondition();

		// skill 02 (��Ŭ����: �ߵ� ���� �߻�)
		bool IsSecondSkillBeginEnterCondition();
		bool IsSecondSkillBeginExitCondition();

		bool IsSecondSkillEnterCondition();
		bool IsSecondSkillExitCondition();

		bool IsSecondSkillEndEnterCondition();
		bool IsSecondSkillEndExitCondition();

		// skill 03 (��Ŭ����: �ߵ� �� ���� �� ������, WAIT �ִϸ��̼� Ȱ��)
		bool IsThirdSkillBeginEnterCondition();
		bool IsThirdSkillBeginExitCondition();

		bool IsThirdSkillEnterCondition();
		bool IsThirdSkillExitCondition();

		bool IsThirdSkillEndEnterCondition();
		bool IsThirdSkillEndExitCondition();

		// skill 04 (��Ŭ����:
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
		// ���� �Ŵ���
		std::weak_ptr<CGameManager> m_wpGameManager;

		// ������
		std::weak_ptr<CSurvivor> m_wpSurvivor;

		// ����
		std::weak_ptr<CBoss> m_wpBoss;

	protected:
		// ���� ����
		EBossState m_eBossState = EBossState::ENUM_END;

		// �ִ� ���� �ð�
		float m_fMaxChaseSeconds = 5.0f;

		// ���� ���� �ð�
		float m_fSumChaseSeconds = 0.0f;

		// �ִ� ��ȸ �ð�
		float m_fMaxWanderSeconds = 10.0f;

		// ���� ��ȸ �ð�
		float m_fSumWanderSeconds = 0.0f;

		// �ִ� ��� �ð�
		float m_fMaxWaitSeconds = 2.0f;

		// ���� ��� �ð�
		float m_fSumWaitSeconds = 0.0f;

		// �ִ� ���� Ƚ��
		int32 m_iMaxAttack = 4;

		// ���� ���� Ƚ��
		int32 m_iSumAttack = 0;
	};
}
