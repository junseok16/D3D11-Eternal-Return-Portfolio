#include "pch.h"
#include "WildAnimalStateComponent.h"

#include "Survivor.h"
#include "WildAnimal.h"

#include "GameManager.h"

HRESULT Client::CWildAnimalStateComponent::PreInitializeComponent()
{
	if (FAILED(CStateComponent::PreInitializeComponent())) { return E_FAIL; }

	// 게임 인스턴스를 불러옵니다.
	m_wpGameManager = CGameManager::GetInstance();
	return S_OK;
}

HRESULT Client::CWildAnimalStateComponent::InitializeComponent()
{
	if (FAILED(CStateComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CWildAnimalStateComponent::PostInitializeComponent()
{
	if (FAILED(CStateComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CWildAnimalStateComponent::BeginPlay()
{
	if (FAILED(CStateComponent::BeginPlay())) { return E_FAIL; }
	
	m_wpSurvivor = m_wpGameManager.lock()->GetSurvivor();
	m_wpWildAnimal = dynamic_pointer_cast<CWildAnimal>(m_wpOwnerActor.lock());
	m_eWildAnimalHabitType = m_wpWildAnimal.lock()->GetWildAnimalHabit();

	switch (m_eWildAnimalHabitType)
	{
	case Client::EWildAnimalHabitType::DIURNAL:
	{
		m_eWildAnimalState = EWildAnimalState::WAIT;
	}	
	break;

	case Client::EWildAnimalHabitType::NOCTURNAL:
	{
		switch (m_wpGameManager.lock()->GetDayType())
		{
		case EDayType::DAY:		m_eWildAnimalState = EWildAnimalState::SLEEP_BEGIN;	break;
		case EDayType::NIGHT:	m_eWildAnimalState = EWildAnimalState::SLEEP_BEGIN;	break;
		default:																	break;
		}
	}
	break;

	default:
	{
		CHECKF(false, L"Wild animal's habit is not designated.")
	}
	break;
	}

	// 진입 조건을 초기화합니다.
	// sleep begin
	AddEnterCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::SLEEP_BEGIN),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsSleepBeginEnterCondition
		);

	// sleep
	AddEnterCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::SLEEP),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsSleepEnterCondition
		);

	// wake
	AddEnterCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::WAKE),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsWakeEnterCondition
		);

	// wait
	AddEnterCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::WAIT),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsWaitEnterCondition
		);

	// beware begin
	AddEnterCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::BEWARE_BEGIN),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsBewareBeginEnterCondition
		);

	// beware
	AddEnterCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::BEWARE),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsBewareEnterCondition
		);

	// beware end
	AddEnterCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::BEWARE_END),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsBewareEndEnterCondition
		);

	// run
	AddEnterCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::RUN),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsRunEnterCondition
		);

	// attack
	AddEnterCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::ATTACK_01),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsFirstAttackEnterCondition
		);

	AddEnterCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::ATTACK_02),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsSecondAttackEnterCondition
		);

	// skill begin
	AddEnterCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::SKILL_BEGIN),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsSkillBeginEnterCondition
		);

	// skill
	AddEnterCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::SKILL),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsSkillEnterCondition
		);

	// end battle
	AddEnterCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::END_BATTLE),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsEndBattleEnterCondition
		);

	// death
	AddEnterCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::DEATH),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsDeathEnterCondition
		);

	// 진출 조건을 초기화합니다.
	// sleep begin
	AddExitCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::SLEEP_BEGIN),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsSleepBeginExitCondition
		);

	// sleep
	AddExitCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::SLEEP),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsSleepExitCondition
		);

	// wake
	AddExitCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::WAKE),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsWakeExitCondition
		);

	// wait
	AddExitCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::WAIT),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsWaitExitCondition
		);

	// beware begin
	AddExitCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::BEWARE_BEGIN),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsBewareBeginExitCondition
		);

	// beware
	AddExitCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::BEWARE),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsBewareExitCondition
		);

	// beware end
	AddExitCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::BEWARE_END),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsBewareEndExitCondition
		);

	// run
	AddExitCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::RUN),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsRunExitCondition
		);

	// attack
	AddExitCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::ATTACK_01),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsFirstAttackExitCondition
		);

	AddExitCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::ATTACK_02),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsSecondAttackExitCondition
		);

	// skill begin
	AddExitCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::SKILL_BEGIN),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsSkillBeginExitCondition
		);

	// skill
	AddExitCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::SKILL),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsSkillExitCondition
		);

	// end battle
	AddExitCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::END_BATTLE),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsEndBattleExitCondition
		);

	// death
	AddExitCondition<CWildAnimalStateComponent>
		(
			static_cast<uint32>(EWildAnimalAnimState::DEATH),
			static_pointer_cast<CWildAnimalStateComponent>(shared_from_this()),
			&CWildAnimalStateComponent::IsDeathExitCondition
		);

	// 주행성 야생 동물은 WAIT, 야행성 야생 동물은 SLEEP_BEGIN 상태가 기본입니다.
	PushAnimState(static_cast<uint32>(m_eWildAnimalState));
	return S_OK;
}

int32 Client::CWildAnimalStateComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CStateComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CWildAnimalStateComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CStateComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CWildAnimalStateComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CStateComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

HRESULT Client::CWildAnimalStateComponent::EndPlay()
{
	if (FAILED(CStateComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CWildAnimalStateComponent::Render()
{
	CStateComponent::Render();
}

void Client::CWildAnimalStateComponent::Release()
{
	CStateComponent::Release();
}

bool Client::CWildAnimalStateComponent::IsSleepBeginEnterCondition()
{
	switch (m_eWildAnimalHabitType)
	{
	case Client::EWildAnimalHabitType::DIURNAL:		return false;
	case Client::EWildAnimalHabitType::NOCTURNAL:
	{
		if (m_eWildAnimalState == EWildAnimalState::SLEEP_BEGIN)
		{
			return true;
		}
		return false;
	}
	default:										return false;
	}
}

bool Client::CWildAnimalStateComponent::IsSleepEnterCondition()
{
	switch (m_eWildAnimalHabitType)
	{
	case Client::EWildAnimalHabitType::DIURNAL:		return false;
	case Client::EWildAnimalHabitType::NOCTURNAL:	return m_eWildAnimalState == EWildAnimalState::SLEEP ? true : false;
	default:										return false;
	}
}

bool Client::CWildAnimalStateComponent::IsWakeEnterCondition()
{
	switch (m_eWildAnimalHabitType)
	{
	case Client::EWildAnimalHabitType::DIURNAL:		return false;
	case Client::EWildAnimalHabitType::NOCTURNAL:	return m_eWildAnimalState == EWildAnimalState::WAKE ? true : false;
	default:										return false;
	}
}

bool Client::CWildAnimalStateComponent::IsWaitEnterCondition()
{
	switch (m_eWildAnimalHabitType)
	{
	case Client::EWildAnimalHabitType::DIURNAL:		return true;
	case Client::EWildAnimalHabitType::NOCTURNAL:	return m_eWildAnimalState == EWildAnimalState::WAIT ? true : false;
	default:										return false;
	}
}

bool Client::CWildAnimalStateComponent::IsBewareBeginEnterCondition()
{
	return m_eWildAnimalState == EWildAnimalState::BEWARE_BEGIN ? true : false;
}

bool Client::CWildAnimalStateComponent::IsBewareEnterCondition()
{
	return m_eWildAnimalState == EWildAnimalState::BEWARE ? true : false;
}

bool Client::CWildAnimalStateComponent::IsBewareEndEnterCondition()
{
	return m_eWildAnimalState == EWildAnimalState::BEWARE_END ? true : false;
}

bool Client::CWildAnimalStateComponent::IsRunEnterCondition()
{
	if (m_eWildAnimalState == EWildAnimalState::CHASE) { return true; }

	if (m_eWildAnimalState == EWildAnimalState::RETREAT) { return true; }

	return false;
}

bool Client::CWildAnimalStateComponent::IsFirstAttackEnterCondition()
{
	return m_eWildAnimalState == EWildAnimalState::ATTACK_01 ? true : false;
}

bool Client::CWildAnimalStateComponent::IsSkillEnterCondition()
{
	return m_eWildAnimalState == EWildAnimalState::SKILL ? true : false;
}

bool Client::CWildAnimalStateComponent::IsSecondAttackEnterCondition()
{
	return m_eWildAnimalState == EWildAnimalState::ATTACK_02 ? true : false;
}

bool Client::CWildAnimalStateComponent::IsSecondAttackExitCondition()
{
	return m_eWildAnimalState != EWildAnimalState::ATTACK_02 ? true : false;
}

bool Client::CWildAnimalStateComponent::IsEndBattleEnterCondition()
{
	return m_eWildAnimalState == EWildAnimalState::END_BATTLE ? true : false;
}

bool Client::CWildAnimalStateComponent::IsDeathEnterCondition()
{
	return m_eWildAnimalState == EWildAnimalState::DEATH ? true : false;
}

bool Client::CWildAnimalStateComponent::IsAppearEnterCondition()
{
	return false;
}

bool Client::CWildAnimalStateComponent::IsDanceEnterCondition()
{
	return false;
}



bool Client::CWildAnimalStateComponent::IsSleepBeginExitCondition()
{
	switch (m_eWildAnimalHabitType)
	{
	case Client::EWildAnimalHabitType::DIURNAL:		return false;
	case Client::EWildAnimalHabitType::NOCTURNAL:	return m_eWildAnimalState != EWildAnimalState::SLEEP_BEGIN ? true : false;
	default:										return false;
	}
}

bool Client::CWildAnimalStateComponent::IsSleepExitCondition()
{
	switch (m_eWildAnimalHabitType)
	{
	case Client::EWildAnimalHabitType::DIURNAL:		return false;
	case Client::EWildAnimalHabitType::NOCTURNAL:	return m_eWildAnimalState != EWildAnimalState::SLEEP ? true : false;
	default:										return false;
	}
}

bool Client::CWildAnimalStateComponent::IsWakeExitCondition()
{
	switch (m_eWildAnimalHabitType)
	{
	case Client::EWildAnimalHabitType::DIURNAL:		return false;
	case Client::EWildAnimalHabitType::NOCTURNAL:	return m_eWildAnimalState != EWildAnimalState::WAKE ? true : false;
	default:										return false;
	}
}

bool Client::CWildAnimalStateComponent::IsWaitExitCondition()
{
	switch (m_eWildAnimalHabitType)
	{
	case Client::EWildAnimalHabitType::DIURNAL:		return false;
	case Client::EWildAnimalHabitType::NOCTURNAL:	return m_eWildAnimalState != EWildAnimalState::WAIT ? true : false;
	default:										return false;
	}
}

bool Client::CWildAnimalStateComponent::IsBewareBeginExitCondition()
{
	return m_eWildAnimalState != EWildAnimalState::BEWARE_BEGIN ? true : false;
}

bool Client::CWildAnimalStateComponent::IsBewareExitCondition()
{
	return m_eWildAnimalState != EWildAnimalState::BEWARE ? true : false;
}

bool Client::CWildAnimalStateComponent::IsBewareEndExitCondition()
{
	return m_eWildAnimalState != EWildAnimalState::BEWARE_END ? true : false;
}

bool Client::CWildAnimalStateComponent::IsRunExitCondition()
{
	return (m_eWildAnimalState != EWildAnimalState::CHASE) && (m_eWildAnimalState != EWildAnimalState::RETREAT) ? true : false;
}

bool Client::CWildAnimalStateComponent::IsSkillBeginEnterCondition()
{
	return m_eWildAnimalState == EWildAnimalState::SKILL_BEGIN ? true : false;
}

bool Client::CWildAnimalStateComponent::IsSkillBeginExitCondition()
{
	return m_eWildAnimalState != EWildAnimalState::SKILL_BEGIN ? true : false;
}

bool Client::CWildAnimalStateComponent::IsFirstAttackExitCondition()
{
	return m_eWildAnimalState != EWildAnimalState::ATTACK_01 ? true : false;
}

bool Client::CWildAnimalStateComponent::IsSkillExitCondition()
{
	return m_eWildAnimalState != EWildAnimalState::SKILL ? true : false;
}

bool Client::CWildAnimalStateComponent::IsEndBattleExitCondition()
{
	return m_eWildAnimalState != EWildAnimalState::END_BATTLE ? true : false;
}

bool Client::CWildAnimalStateComponent::IsDeathExitCondition()
{
	return false;
}

bool Client::CWildAnimalStateComponent::IsAppearExitCondition()
{
	return false;
}

bool Client::CWildAnimalStateComponent::IsDanceExitCondition()
{
	return false;
}

void Client::CWildAnimalStateComponent::OnAnimEnter(uint32 _iAnimState, float _fRatio)
{
}

void Client::CWildAnimalStateComponent::OnAnimStay(uint32 _iAnimState, float _fRatio)
{
}

void Client::CWildAnimalStateComponent::OnAnimExit(uint32 _iAnimState, float _fRatio)
{
	switch (static_cast<EWildAnimalAnimState>(_iAnimState))
	{
	case EWildAnimalAnimState::SLEEP_BEGIN:		m_eWildAnimalState = EWildAnimalState::SLEEP;			break;
	case EWildAnimalAnimState::SLEEP:																	break;
	case EWildAnimalAnimState::WAKE:			m_eWildAnimalState = EWildAnimalState::BEWARE_BEGIN;	break;
	case EWildAnimalAnimState::WAIT:																	break;
	case EWildAnimalAnimState::BEWARE_BEGIN:	m_eWildAnimalState = EWildAnimalState::BEWARE;			break;
	case EWildAnimalAnimState::BEWARE:																	break;

	case EWildAnimalAnimState::BEWARE_END:

		switch (m_eWildAnimalHabitType)
		{
		case Client::EWildAnimalHabitType::DIURNAL:
			m_eWildAnimalState = EWildAnimalState::WAIT;
			break;

		case Client::EWildAnimalHabitType::NOCTURNAL:
			if (m_wpGameManager.lock()->GetDayType() == EDayType::DAY)
			{
				m_eWildAnimalState = EWildAnimalState::SLEEP_BEGIN;
			}
			else
			{
				m_eWildAnimalState = EWildAnimalState::WAIT;
			}
			break;

		default:
			break;
		}

		break;

	case EWildAnimalAnimState::RUN:																		break;
	case EWildAnimalAnimState::ATTACK_01:																break;
	case EWildAnimalAnimState::ATTACK_02:																break;
	case EWildAnimalAnimState::SKILL:																	break;
	case EWildAnimalAnimState::END_BATTLE:		m_eWildAnimalState = EWildAnimalState::RETREAT;			break;
	case EWildAnimalAnimState::DEATH:																	break;
	case EWildAnimalAnimState::DANCE:																	break;
	default:																							break;
	}
}

void Client::CWildAnimalStateComponent::UpdateWildAnimalState(float _fDeltaSeconds)
{
	// 낮밤 타입을 업데이트합니다.
	m_eDayType = m_wpGameManager.lock()->GetDayType();

	Vector3 vSurvivorPosition = m_wpGameManager.lock()->GetSurvivor()->GetActorWorldPosition().value();
	Vector3 vWildAnimalPosition = m_wpWildAnimal.lock()->GetActorWorldPosition().value();

	Vector3 vDistance = vSurvivorPosition - vWildAnimalPosition;
	float fDistance = vDistance.Length();

	switch (m_eWildAnimalState)
	{
	case Client::EWildAnimalState::SLEEP_BEGIN:
	{
		// 체력이 0보다 작은 경우
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}
	}
	break;

	case Client::EWildAnimalState::SLEEP:
	{
		// 체력이 0보다 작은 경우
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}

		switch (m_eWildAnimalHabitType)
		{
		case Client::EWildAnimalHabitType::DIURNAL:
		{

		}
		break;

		case Client::EWildAnimalHabitType::NOCTURNAL:
		{
			// 밤이 된 경우
			if (m_eDayType == EDayType::NIGHT)
			{
				m_eWildAnimalState = EWildAnimalState::WAIT;
				break;
			}

			// 플레이어와 몬스터 사이의 거리가 몬스터의 경계 거리보다 가까운 경우
			if (fDistance <= m_wpWildAnimal.lock()->GetBewareDistance())
			{
				m_eWildAnimalState = EWildAnimalState::WAKE;
				break;
			}
		}
		break;
		}
	}
	break;

	case Client::EWildAnimalState::WAKE:
	{
		// 체력이 0보다 작은 경우
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}
	}
	break;

	case Client::EWildAnimalState::WAIT:
	{
		// 체력이 0보다 작은 경우
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}

		// 플레이어와 몬스터 사이의 거리가 몬스터의 경계 거리보다 가까운 경우
		if (fDistance <= m_wpWildAnimal.lock()->GetBewareDistance())
		{
			m_eWildAnimalState = EWildAnimalState::BEWARE_BEGIN;
			break;
		}

		// 야행성인 경우
		if (m_eWildAnimalHabitType == EWildAnimalHabitType::NOCTURNAL)
		{
			// 낮인 경우
			if (m_eDayType == EDayType::DAY)
			{
				m_eWildAnimalState = EWildAnimalState::SLEEP_BEGIN;
				break;
			}
		}

		// 몬스터가 공격당한 경우
		if (m_wpWildAnimal.lock()->IsAttacked())
		{
			// 플레이어와 몬스터 사이의 거리가 몬스터의 공격 범위보다 긴 경우
			if (fDistance > m_wpWildAnimal.lock()->GetAttackRange())
			{
				m_eWildAnimalState = EWildAnimalState::CHASE;
			}
			else
			{
				m_eWildAnimalState = EWildAnimalState::ATTACK_01;
			}
			break;
		}
	}
	break;

	case Client::EWildAnimalState::BEWARE_BEGIN:
	{
		// 체력이 0보다 작은 경우
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}
	}
	break;

	case Client::EWildAnimalState::BEWARE:
	{	
		// 체력이 0보다 작은 경우
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}

		// 플레이어와 몬스터 사이의 거리가 몬스터의 경계 거리보다 먼 경우
		if (fDistance > m_wpWildAnimal.lock()->GetBewareDistance())
		{
			m_eWildAnimalState = EWildAnimalState::BEWARE_END;
			break;
		}

		// 몬스터가 공격당한 경우
		if (m_wpWildAnimal.lock()->IsAttacked())
		{
			// 플레이어와 몬스터 사이의 거리가 몬스터의 공격 범위보다 긴 경우
			if (fDistance > m_wpWildAnimal.lock()->GetAttackRange())
			{
				m_eWildAnimalState = EWildAnimalState::CHASE;
			}
			else
			{
				m_eWildAnimalState = EWildAnimalState::ATTACK_01;
			}
			break;
		}
	}
	break;

	case Client::EWildAnimalState::BEWARE_END:
	{
		// 체력이 0보다 작은 경우
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}
	}
	break;

	case Client::EWildAnimalState::ATTACK_01:
	{	
		// 체력이 0보다 작은 경우
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_wpWildAnimal.lock()->SetAttacked(false);
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}

		// 플레이어와 몬스터 사이의 거리가 몬스터의 공격 범위보다 긴 경우
		if (fDistance > m_wpWildAnimal.lock()->GetAttackRange())
		{
			m_eWildAnimalState = EWildAnimalState::CHASE;
			break;
		}
	}
	break;

	case Client::EWildAnimalState::CHASE:
	{
		m_fSumChaseSeconds += _fDeltaSeconds;

		// 체력이 0보다 작은 경우
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_fSumChaseSeconds = 0.0f;
			m_wpWildAnimal.lock()->SetAttacked(false);
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}

		// 플레이어와 몬스터 사이의 거리가 몬스터의 공격 범위보다 짧은 경우
		if (fDistance <= m_wpWildAnimal.lock()->GetAttackRange())
		{
			m_fSumChaseSeconds = 0.0f;
			m_eWildAnimalState = EWildAnimalState::ATTACK_01;
			break;
		}

		// 누적 추적 시간이 최대 추적 시간보다 많은 경우
		if (m_fSumChaseSeconds > m_fMaxChaseSeconds)
		{
			Vector3 vSpawnPosition = m_wpWildAnimal.lock()->GetSpawnPosition();
			m_fMaxDistance = Vector3::Distance(vSpawnPosition, vWildAnimalPosition);

			// m_fSumChaseSeconds = 0.0f;
			m_wpWildAnimal.lock()->SetAttacked(false);
			m_eWildAnimalState = EWildAnimalState::END_BATTLE;
			break;
		}
	}
	break;

	case Client::EWildAnimalState::END_BATTLE:
	{
		// 체력이 0보다 작은 경우
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_wpWildAnimal.lock()->SetAttacked(false);
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}
	}
	break;

	case Client::EWildAnimalState::RETREAT:
	{
		// 체력이 0보다 작은 경우
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}

		if (m_vecMementos.empty())
		{
			switch (m_eWildAnimalHabitType)
			{
			case Client::EWildAnimalHabitType::DIURNAL:
				m_eWildAnimalState = EWildAnimalState::WAIT;
				break;

			case Client::EWildAnimalHabitType::NOCTURNAL:
				if (m_eDayType == EDayType::DAY)
				{
					m_eWildAnimalState = EWildAnimalState::SLEEP_BEGIN;
				}
				else
				{
					m_eWildAnimalState = EWildAnimalState::WAIT;
				}
				break;
			}
		}
	}
	break;

	case Client::EWildAnimalState::DEATH:
	{
		// TODO; 리스폰 시간
	}
	break;

	}
}

void Client::CWildAnimalStateComponent::UpdateWildAnimalBehavior(float _fDeltaSeconds)
{
	switch (m_eWildAnimalState)
	{
	case Client::EWildAnimalState::ATTACK_01:
	{
		Vector3 vPosition = m_wpGameManager.lock()->GetSurvivor()->GetActorWorldPosition().value();
		m_wpWildAnimal.lock()->LookAt(vPosition);
	}
	break;

	case Client::EWildAnimalState::CHASE:
	{
		Vector3 vPosition = m_wpGameManager.lock()->GetSurvivor()->GetActorWorldPosition().value();
		m_wpWildAnimal.lock()->LookAt(vPosition);

		Vector3 vForward = m_wpWildAnimal.lock()->GetActorWorldForwardVector().value();
		Vector3 vWildAnimalPosition = m_wpWildAnimal.lock()->GetActorWorldPosition().value();

		Vector3 vTargetPosition = vWildAnimalPosition + vForward * _fDeltaSeconds * m_wpWildAnimal.lock()->GetCurMoveSpeed();

		m_wpWildAnimal.lock()->SetActorLocalPosition(vTargetPosition);

		m_fSumMementoSeconds += _fDeltaSeconds;
		if (m_fSumMementoSeconds >= m_fMaxMementoSeconds)
		{
			m_fSumMementoSeconds = 0.0f;
			m_vecMementos.emplace_back(vWildAnimalPosition);
		}
	}
	break;

	case Client::EWildAnimalState::END_BATTLE:
	{
		
	}
	break;

	case Client::EWildAnimalState::RETREAT:
	{
		if (m_vecMementos.empty())
		{
			m_fSumChaseSeconds = 0.0f;
			break;
		}

		Vector3 vLatestPosition = m_vecMementos.back();
		m_wpWildAnimal.lock()->LookAt(vLatestPosition);

		Vector3 vForward = m_wpWildAnimal.lock()->GetActorWorldForwardVector().value();
		Vector3 vWildAnimalPosition = m_wpWildAnimal.lock()->GetActorWorldPosition().value();

		Vector3 vDistance = vLatestPosition - vWildAnimalPosition;
		float fDistance = vDistance.Length();

		if (fDistance <= 0.1f)
		{
			m_fSumChaseSeconds = 0.0f;
			m_vecMementos.pop_back();
		}

		Vector3 vSpawnPosition = m_wpWildAnimal.lock()->GetSpawnPosition();
		float fCurDistance = Vector3::Distance(vSpawnPosition, vWildAnimalPosition);

		m_fSumChaseSeconds = m_fMaxChaseSeconds * fCurDistance / m_fMaxDistance;

		Vector3 vTargetPosition = vWildAnimalPosition + vForward * _fDeltaSeconds * m_wpWildAnimal.lock()->GetCurMoveSpeed();
		m_wpWildAnimal.lock()->SetActorLocalPosition(vTargetPosition);
	}
	break;

	case Client::EWildAnimalState::SKILL_BEGIN:
	break;

	case Client::EWildAnimalState::SKILL:
	break;

	case Client::EWildAnimalState::DEATH:
	break;
	}
}
