#include "pch.h"
#include "BearStateComponent.h"

#include "NavigationComponent.h"

#include "Survivor.h"
#include "WildAnimal.h"

#include "GameManager.h"

HRESULT Client::CBearStateComponent::PreInitializeComponent()
{
	if (FAILED(CWildAnimalStateComponent::PreInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CBearStateComponent::InitializeComponent()
{
	if (FAILED(CWildAnimalStateComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CBearStateComponent::PostInitializeComponent()
{
	if (FAILED(CWildAnimalStateComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CBearStateComponent::BeginPlay()
{
	if (FAILED(CWildAnimalStateComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CBearStateComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CWildAnimalStateComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CBearStateComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CWildAnimalStateComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	UpdateWildAnimalState(_fDeltaSeconds);
	UpdateWildAnimalBehavior(_fDeltaSeconds);
	return 0;
}

int32 Client::CBearStateComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CWildAnimalStateComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CBearStateComponent::EndPlay()
{
	if (FAILED(CWildAnimalStateComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CBearStateComponent::Render()
{
	CWildAnimalStateComponent::Render();
}

void Client::CBearStateComponent::Release()
{
	CWildAnimalStateComponent::Release();
}

void Client::CBearStateComponent::UpdateWildAnimalState(float _fDeltaSeconds)
{
	// 낮밤 타입을 업데이트합니다.
	m_eDayType = m_wpGameManager.lock()->GetDayType();

	Vector3 vSurvivorPosition = m_wpGameManager.lock()->GetSurvivor()->GetActorWorldPosition().value();
	Vector3 vWildAnimalPosition = m_wpWildAnimal.lock()->GetActorWorldPosition().value();
	float fDistance = Vector3::Distance(vSurvivorPosition, vWildAnimalPosition);

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
				if (m_ePreAttackState == EWildAnimalState::ATTACK_01)
				{
					m_ePreAttackState = EWildAnimalState::ATTACK_02;
					m_eWildAnimalState = EWildAnimalState::ATTACK_02;
				}
				else if (m_ePreAttackState == EWildAnimalState::ATTACK_02)
				{
					m_ePreAttackState = EWildAnimalState::ATTACK_01;
					m_eWildAnimalState = EWildAnimalState::ATTACK_01;
				}
			}
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
				if (m_ePreAttackState == EWildAnimalState::ATTACK_01)
				{
					m_ePreAttackState = EWildAnimalState::ATTACK_02;
					m_eWildAnimalState = EWildAnimalState::ATTACK_02;
				}
				else if (m_ePreAttackState == EWildAnimalState::ATTACK_02)
				{
					m_ePreAttackState = EWildAnimalState::ATTACK_01;
					m_eWildAnimalState = EWildAnimalState::ATTACK_01;
				}
			}
			break;
		}

		switch (m_eWildAnimalHabitType)
		{
		case Client::EWildAnimalHabitType::DIURNAL:
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
				if (m_ePreAttackState == EWildAnimalState::ATTACK_01)
				{
					m_ePreAttackState = EWildAnimalState::ATTACK_02;
					m_eWildAnimalState = EWildAnimalState::ATTACK_02;
				}
				else if (m_ePreAttackState == EWildAnimalState::ATTACK_02)
				{
					m_ePreAttackState = EWildAnimalState::ATTACK_01;
					m_eWildAnimalState = EWildAnimalState::ATTACK_01;
				}
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
				if (m_ePreAttackState == EWildAnimalState::ATTACK_01)
				{
					m_ePreAttackState = EWildAnimalState::ATTACK_02;
					m_eWildAnimalState = EWildAnimalState::ATTACK_02;
				}
				else if (m_ePreAttackState == EWildAnimalState::ATTACK_02)
				{
					m_ePreAttackState = EWildAnimalState::ATTACK_01;
					m_eWildAnimalState = EWildAnimalState::ATTACK_01;
				}
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
	case Client::EWildAnimalState::ATTACK_02:
	{
		// 체력이 0보다 작은 경우
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_wpWildAnimal.lock()->SetAttacked(false);
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}

		/*
		// 플레이어와 몬스터 사이의 거리가 몬스터의 공격 범위보다 긴 경우
		if (fDistance > m_wpWildAnimal.lock()->GetAttackRange())
		{
			m_eWildAnimalState = EWildAnimalState::CHASE;
			break;
		}
		*/
	}
	break;

	case Client::EWildAnimalState::SKILL:
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

			if (m_ePreAttackState == EWildAnimalState::ATTACK_01)
			{
				m_ePreAttackState = EWildAnimalState::ATTACK_02;
				m_eWildAnimalState = EWildAnimalState::ATTACK_02;
			}
			else if (m_ePreAttackState == EWildAnimalState::ATTACK_02)
			{
				m_ePreAttackState = EWildAnimalState::ATTACK_01;
				m_eWildAnimalState = EWildAnimalState::ATTACK_01;
			}

			break;
		}

		// 누적 추적 시간이 최대 추적 시간보다 많은 경우
		if (m_fSumChaseSeconds > m_fMaxChaseSeconds)
		{
			m_fSumChaseSeconds = 0.0f;
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
		// m_wpWildAnimal.lock()->SetAttacked(false);

		// 체력이 0보다 작은 경우
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}

		Vector3 vSpawnPosition = m_wpWildAnimal.lock()->GetSpawnPosition();
		Vector3 vWildAnimalPosition = m_wpWildAnimal.lock()->GetActorWorldPosition().value();
		float fDistance = Vector3::Distance(vSpawnPosition, vWildAnimalPosition);

		if (fDistance <= 1.5f)
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

void Client::CBearStateComponent::UpdateWildAnimalBehavior(float _fDeltaSeconds)
{
	switch (m_eWildAnimalState)
	{
	case Client::EWildAnimalState::ATTACK_01:
	case Client::EWildAnimalState::ATTACK_02:
	{
		Vector3 vPosition = m_wpGameManager.lock()->GetSurvivor()->GetActorWorldPosition().value();
		m_wpWildAnimal.lock()->LookAt(vPosition);
	}
	break;

	case Client::EWildAnimalState::CHASE:
	{
		Vector3 vSurvivorPosition = m_wpGameManager.lock()->GetSurvivor()->GetActorWorldPosition().value();
		m_wpWildAnimal.lock()->LookAt(vSurvivorPosition);

		Vector3 vForward = m_wpWildAnimal.lock()->GetActorWorldForwardVector().value();
		Vector3 vWildAnimalPosition = m_wpWildAnimal.lock()->GetActorWorldPosition().value();

		Vector3 vTargetPosition = vWildAnimalPosition + vForward * _fDeltaSeconds * m_wpWildAnimal.lock()->GetCurMoveSpeed();

		Vector3 vOutWorldPosition = Vector3::Zero;
		if (!m_wpWildAnimal.lock()->GetNavigationComponent()->IsValidCell(vTargetPosition, vOutWorldPosition))
		{
			break;
		}
		m_wpWildAnimal.lock()->SetActorLocalPosition(vOutWorldPosition);

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
		Vector3 vLatestPosition = m_vecMementos.back();// vWildAnimalPosition + vForward * _fDeltaSeconds * m_wpWildAnimal.lock()->GetCurMoveSpeed();
		m_wpWildAnimal.lock()->LookAt(vLatestPosition);

		Vector3 vForward = m_wpWildAnimal.lock()->GetActorWorldForwardVector().value();
		Vector3 vWildAnimalPosition = m_wpWildAnimal.lock()->GetActorWorldPosition().value();
		float fDistance = Vector3::Distance(vLatestPosition, vWildAnimalPosition);

		if (fDistance <= 0.1f)
		{
			if (m_vecMementos.size() == 1) { break; }

			m_vecMementos.pop_back();
		}

		Vector3 vTargetPosition = vWildAnimalPosition + vForward * _fDeltaSeconds * m_wpWildAnimal.lock()->GetCurMoveSpeed();

		Vector3 vOutWorldPosition = Vector3::Zero;
		if (!m_wpWildAnimal.lock()->GetNavigationComponent()->IsValidCell(vTargetPosition, vOutWorldPosition))
		{
			break;
		}
		m_wpWildAnimal.lock()->SetActorLocalPosition(vOutWorldPosition);
	}
	break;

	case Client::EWildAnimalState::SKILL:
	{

	}
	break;

	case Client::EWildAnimalState::DEATH:
	{

	}
	break;
	}
}

void Client::CBearStateComponent::OnAnimEnter(uint32 _iAnimState, float _fRatio)
{
}

void Client::CBearStateComponent::OnAnimStay(uint32 _iAnimState, float _fRatio)
{
}

void Client::CBearStateComponent::OnAnimExit(uint32 _iAnimState, float _fRatio)
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
	{
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
		}
	}
	break;

	case EWildAnimalAnimState::RUN:																		break;
	case EWildAnimalAnimState::ATTACK_01:
	case EWildAnimalAnimState::ATTACK_02:
	{
		if (m_ePreAttackState == EWildAnimalState::ATTACK_01)
		{
			m_ePreAttackState = EWildAnimalState::ATTACK_02;
			m_eWildAnimalState = EWildAnimalState::ATTACK_02;
		}
		else if (m_ePreAttackState == EWildAnimalState::ATTACK_02)
		{
			m_ePreAttackState = EWildAnimalState::ATTACK_01;
			m_eWildAnimalState = EWildAnimalState::ATTACK_01;
		}

		m_iSumSAttack++;
		if (m_iSumSAttack == m_iMaxAttack)
		{
			m_iSumSAttack = 0;
			m_eWildAnimalState = EWildAnimalState::SKILL;
		}

		Vector3 vSurvivorPosition = m_wpGameManager.lock()->GetSurvivor()->GetActorWorldPosition().value();
		Vector3 vWildAnimalPosition = m_wpWildAnimal.lock()->GetActorWorldPosition().value();
		float fDistance = Vector3::Distance(vSurvivorPosition, vWildAnimalPosition);

		// 플레이어와 몬스터 사이의 거리가 몬스터의 공격 범위보다 긴 경우
		if (fDistance > m_wpWildAnimal.lock()->GetAttackRange())
		{
			m_eWildAnimalState = EWildAnimalState::CHASE;
			break;
		}
	}
	break;
	case EWildAnimalAnimState::SKILL:			m_eWildAnimalState = EWildAnimalState::CHASE;			break;
	case EWildAnimalAnimState::END_BATTLE:		m_eWildAnimalState = EWildAnimalState::RETREAT;			break;
	case EWildAnimalAnimState::DEATH:																	break;
	case EWildAnimalAnimState::DANCE:																	break;
	default:																							break;
	}
}
