#include "pch.h"
#include "BossStateComponent.h"

#include "Boss.h"

#include "Survivor.h"
#include "GameManager.h"

HRESULT Client::CBossStateComponent::PreInitializeComponent()
{
	if (FAILED(CStateComponent::PreInitializeComponent())) { return E_FAIL; }

	// 게임 인스턴스를 불러옵니다.
	m_wpGameManager = CGameManager::GetInstance();
	return S_OK;
}

HRESULT Client::CBossStateComponent::InitializeComponent()
{
	if (FAILED(CStateComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CBossStateComponent::PostInitializeComponent()
{
	if (FAILED(CStateComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CBossStateComponent::BeginPlay()
{
	if (FAILED(CStateComponent::BeginPlay())) { return E_FAIL; }

	m_wpSurvivor = m_wpGameManager.lock()->GetSurvivor();
	m_wpBoss = dynamic_pointer_cast<CBoss>(m_wpOwnerActor.lock());
	m_eBossState = EBossState::WANDER;

	// 진입 조건을 초기화합니다.
	// wait
	AddEnterCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::WAIT),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsWaitEnterCondition
		);

	// run
	AddEnterCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::RUN),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsRunEnterCondition
		);

	// attack 01
	AddEnterCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::ATTACK_01),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsFirstAttackEnterCondition
		);

	// attack 02
	AddEnterCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::ATTACK_02),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsSecondAttackEnterCondition
		);

	// skill 01 begin
	AddEnterCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::SKILL_01_BEGIN),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsFirstSkillBeginEnterCondition
		);

	// skill 01
	AddEnterCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::SKILL_01),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsFirstSkillEnterCondition
		);

	// skill 01 end
	AddEnterCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::SKILL_01_END),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsFirstSkillEndEnterCondition
		);

	// skill 02 begin
	AddEnterCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::SKILL_02_BEGIN),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsSecondSkillBeginEnterCondition
		);

	// skill 02
	AddEnterCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::SKILL_02),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsSecondSkillEnterCondition
		);

	// skill 02 end
	AddEnterCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::SKILL_02_END),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsSecondSkillEndEnterCondition
		);

	// skill 03
	AddEnterCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::SKILL_03),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsThirdSkillEnterCondition
		);

	// end battle
	AddEnterCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::END_BATTLE),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsEndBattleEnterCondition
		);

	// death
	AddEnterCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::DEATH),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsDeathEnterCondition
		);


	// 진출 조건을 초기화합니다.
	// wait
	AddExitCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::WAIT),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsWaitExitCondition
		);

	// run
	AddExitCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::RUN),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsRunExitCondition
		);

	// attack 01
	AddExitCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::ATTACK_01),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsFirstAttackExitCondition
		);

	// attack 02
	AddExitCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::ATTACK_02),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsSecondAttackExitCondition
		);

	// skill 01 begin
	AddExitCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::SKILL_01_BEGIN),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsFirstSkillBeginExitCondition
		);

	// skill 01
	AddExitCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::SKILL_01),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsFirstSkillExitCondition
		);

	// skill 01 end
	AddExitCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::SKILL_01_END),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsFirstSkillEndExitCondition
		);

	// skill 02 begin
	AddExitCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::SKILL_02_BEGIN),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsSecondSkillBeginExitCondition
		);

	// skill 02
	AddExitCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::SKILL_02),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsSecondSkillExitCondition
		);

	// skill 02 end
	AddExitCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::SKILL_02_END),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsSecondSkillEndExitCondition
		);

	// skill 03
	AddExitCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::SKILL_03),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsThirdSkillExitCondition
		);

	// end battle
	AddExitCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::END_BATTLE),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsEndBattleExitCondition
		);

	// death
	AddExitCondition<CBossStateComponent>
		(
			static_cast<uint32>(EBossAnimState::DEATH),
			static_pointer_cast<CBossStateComponent>(shared_from_this()),
			&CBossStateComponent::IsDeathExitCondition
		);

	PushAnimState(static_cast<uint32>(m_eBossState));
	return S_OK;
}

int32 Client::CBossStateComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CStateComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CBossStateComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CStateComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CBossStateComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CStateComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

HRESULT Client::CBossStateComponent::EndPlay()
{
	if (FAILED(CStateComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CBossStateComponent::Render()
{
	CStateComponent::Render();
}

void Client::CBossStateComponent::Release()
{
	CStateComponent::Release();
}

bool Client::CBossStateComponent::IsWaitEnterCondition()
{
	return m_eBossState == EBossState::WAIT ? true : false;
}

bool Client::CBossStateComponent::IsWaitExitCondition()
{
	return false;
}

bool Client::CBossStateComponent::IsRunEnterCondition()
{
	if (m_eBossState == EBossState::CHASE) { return true; }

	if (m_eBossState == EBossState::WANDER) { return true; }

	return false;
}

bool Client::CBossStateComponent::IsRunExitCondition()
{
	if (m_eBossState == EBossState::CHASE) { return false; }

	if (m_eBossState == EBossState::WANDER) { return false; }

	return true;
}

bool Client::CBossStateComponent::IsFirstSkillBeginEnterCondition()
{
	return m_eBossState == EBossState::SKILL_01_BEGIN ? true : false;
}

bool Client::CBossStateComponent::IsFirstSkillBeginExitCondition()
{
	return m_eBossState != EBossState::SKILL_01_BEGIN ? true : false;
}

bool Client::CBossStateComponent::IsFirstSkillEnterCondition()
{
	return m_eBossState == EBossState::SKILL_01 ? true : false;
}

bool Client::CBossStateComponent::IsFirstSkillExitCondition()
{
	return m_eBossState != EBossState::SKILL_01 ? true : false;
}

bool Client::CBossStateComponent::IsFirstSkillEndEnterCondition()
{
	return m_eBossState == EBossState::SKILL_01_END ? true : false;
}

bool Client::CBossStateComponent::IsFirstSkillEndExitCondition()
{
	return m_eBossState != EBossState::SKILL_01_END ? true : false;
}

bool Client::CBossStateComponent::IsSecondSkillBeginEnterCondition()
{
	return m_eBossState == EBossState::SKILL_02_BEGIN ? true : false;
}

bool Client::CBossStateComponent::IsSecondSkillBeginExitCondition()
{
	return m_eBossState != EBossState::SKILL_02_BEGIN ? true : false;
}

bool Client::CBossStateComponent::IsSecondSkillEnterCondition()
{
	return m_eBossState == EBossState::SKILL_02 ? true : false;
}

bool Client::CBossStateComponent::IsSecondSkillExitCondition()
{
	return m_eBossState != EBossState::SKILL_02 ? true : false;
}

bool Client::CBossStateComponent::IsSecondSkillEndEnterCondition()
{
	return m_eBossState == EBossState::SKILL_02_END ? true : false;
}

bool Client::CBossStateComponent::IsSecondSkillEndExitCondition()
{
	return m_eBossState != EBossState::SKILL_02_END ? true : false;
}

bool Client::CBossStateComponent::IsThirdSkillBeginEnterCondition()
{
	return m_eBossState == EBossState::SKILL_03_BEGIN ? true : false;
}

bool Client::CBossStateComponent::IsThirdSkillBeginExitCondition()
{
	return m_eBossState != EBossState::SKILL_03_BEGIN ? true : false;
}

bool Client::CBossStateComponent::IsThirdSkillEnterCondition()
{
	return m_eBossState == EBossState::SKILL_03 ? true : false;
}

bool Client::CBossStateComponent::IsThirdSkillExitCondition()
{
	return m_eBossState != EBossState::SKILL_03 ? true : false;
}

bool Client::CBossStateComponent::IsThirdSkillEndEnterCondition()
{
	return m_eBossState == EBossState::SKILL_03_END ? true : false;
}

bool Client::CBossStateComponent::IsThirdSkillEndExitCondition()
{
	return m_eBossState != EBossState::SKILL_03_END ? true : false;
}

bool Client::CBossStateComponent::IsFirstAttackEnterCondition()
{
	return m_eBossState == EBossState::ATTACK_01 ? true : false;
}

bool Client::CBossStateComponent::IsFirstAttackExitCondition()
{
	return m_eBossState != EBossState::ATTACK_01 ? true : false;
}

bool Client::CBossStateComponent::IsSecondAttackEnterCondition()
{
	return m_eBossState == EBossState::ATTACK_02 ? true : false;
}

bool Client::CBossStateComponent::IsSecondAttackExitCondition()
{
	return m_eBossState != EBossState::ATTACK_02 ? true : false;
}

bool Client::CBossStateComponent::IsEndBattleEnterCondition()
{
	return m_eBossState == EBossState::END_BATTLE ? true : false;
}

bool Client::CBossStateComponent::IsEndBattleExitCondition()
{
	return m_eBossState != EBossState::END_BATTLE ? true : false;
}

bool Client::CBossStateComponent::IsDeathEnterCondition()
{
	return m_eBossState == EBossState::DEATH ? true : false;
}

bool Client::CBossStateComponent::IsDeathExitCondition()
{
	return false;
}

void Client::CBossStateComponent::OnAnimEnter(uint32 _iAnimState, float _fRatio)
{
}

void Client::CBossStateComponent::OnAnimStay(uint32 _iAnimState, float _fRatio)
{
}

void Client::CBossStateComponent::OnAnimExit(uint32 _iAnimState, float _fRatio)
{
}

void Client::CBossStateComponent::UpdateBossState(float _fDeltaSeconds)
{
}

void Client::CBossStateComponent::UpdateBossBehavior(float _fDeltaSeconds)
{
}
