#include "pch.h"
#include "OmegaStateComponent.h"

#include "NavigationComponent.h"
#include "Boss.h"
#include "Survivor.h"

#include "MathUtility.h"

#include "GameManager.h"

HRESULT Editor::COmegaStateComponent::PreInitializeComponent()
{
	if (FAILED(CBossStateComponent::PreInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::COmegaStateComponent::InitializeComponent()
{
	if (FAILED(CBossStateComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::COmegaStateComponent::PostInitializeComponent()
{
	if (FAILED(CBossStateComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::COmegaStateComponent::BeginPlay()
{
	if (FAILED(CBossStateComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::COmegaStateComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CBossStateComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::COmegaStateComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CBossStateComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	UpdateBossState(_fDeltaSeconds);
	UpdateBossBehavior(_fDeltaSeconds);
	return 0;
}

int32 Editor::COmegaStateComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CBossStateComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::COmegaStateComponent::EndPlay()
{
	if (FAILED(CBossStateComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::COmegaStateComponent::Render()
{
	CBossStateComponent::Render();
}

void Editor::COmegaStateComponent::Release()
{
	CBossStateComponent::Release();
}

void Editor::COmegaStateComponent::UpdateBossState(float _fDeltaSeconds)
{
	Vector3 vSurvivorPosition = m_wpGameManager.lock()->GetSurvivor()->GetActorWorldPosition().value();
	Vector3 vBossPosition = m_wpBoss.lock()->GetActorWorldPosition().value();

	Vector3 vDistance = vSurvivorPosition - vBossPosition;
	float fDistance = vDistance.Length();

	switch (m_eBossState)
	{
	case Editor::EBossState::WANDER:
	{
		// 체력이 0보다 작은 경우
		if (m_wpBoss.lock()->GetCurHP() <= 0.0f)
		{
			m_fSumWanderSeconds = 0.0f;

			m_wpBoss.lock()->SetAttacked(false);
			m_eBossState = EBossState::DEATH;
			break;
		}

		// 플레이어와 몬스터 사이의 거리가 몬스터의 경계 거리보다 가까운 경우
		if (fDistance <= m_wpBoss.lock()->GetBewareDistance())
		{
			m_fSumWanderSeconds = 0.0f;

			m_eBossState = EBossState::CHASE;
			break;
		}

		// 몬스터가 공격당한 경우
		if (m_wpBoss.lock()->IsAttacked())
		{
			m_fSumWanderSeconds = 0.0f;

			// 플레이어와 몬스터 사이의 거리가 몬스터의 공격 범위보다 긴 경우
			if (fDistance > m_wpBoss.lock()->GetAttackRange())
			{
				m_eBossState = EBossState::CHASE;
			}
			else
			{
				if (m_ePreAttackState == EBossState::ATTACK_01)
				{
					m_ePreAttackState = EBossState::ATTACK_02;
					m_eBossState = EBossState::ATTACK_02;
				}
				else if (m_ePreAttackState == EBossState::ATTACK_02)
				{
					m_ePreAttackState = EBossState::ATTACK_01;
					m_eBossState = EBossState::ATTACK_01;
				}
			}
			break;
		}

		m_fSumWanderSeconds += _fDeltaSeconds;

		// 누적 배회 시간이 최대 배회 시간보다 많은 경우
		if (m_fSumWanderSeconds > m_fMaxWanderSeconds)
		{
			m_fSumWanderSeconds = 0.0f;
			m_eBossState = EBossState::WAIT;
			break;
		}
	}
	break;

	case Editor::EBossState::WAIT:
	{
		// 체력이 0보다 작은 경우
		if (m_wpBoss.lock()->GetCurHP() <= 0.0f)
		{
			m_fSumWaitSeconds = 0.0f;

			m_wpBoss.lock()->SetAttacked(false);
			m_eBossState = EBossState::DEATH;
			break;
		}

		// 플레이어와 몬스터 사이의 거리가 몬스터의 경계 거리보다 가까운 경우
		if (fDistance <= m_wpBoss.lock()->GetBewareDistance())
		{
			m_fSumWaitSeconds = 0.0f;

			m_eBossState = EBossState::CHASE;
			break;
		}

		// 몬스터가 공격당한 경우
		if (m_wpBoss.lock()->IsAttacked())
		{
			m_fSumWaitSeconds = 0.0f;

			// 플레이어와 몬스터 사이의 거리가 몬스터의 공격 범위보다 긴 경우
			if (fDistance > m_wpBoss.lock()->GetAttackRange())
			{
				m_eBossState = EBossState::CHASE;
			}
			else
			{
				if (m_ePreAttackState == EBossState::ATTACK_01)
				{
					m_ePreAttackState = EBossState::ATTACK_02;
					m_eBossState = EBossState::ATTACK_02;
				}
				else if (m_ePreAttackState == EBossState::ATTACK_02)
				{
					m_ePreAttackState = EBossState::ATTACK_01;
					m_eBossState = EBossState::ATTACK_01;
				}
			}
			break;
		}


		m_fSumWaitSeconds += _fDeltaSeconds;

		// 누적 대기 시간이 최대 대기 시간보다 많은 경우
		if (m_fSumWaitSeconds > m_fMaxWaitSeconds)
		{
			m_fSumWaitSeconds = 0.0f;
			m_eBossState = EBossState::WANDER;
			break;
		}
	}
	break;

	case Editor::EBossState::CHASE:
	{
		// 체력이 0보다 작은 경우
		if (m_wpBoss.lock()->GetCurHP() <= 0.0f)
		{
			m_fSumChaseSeconds = 0.0f;

			m_wpBoss.lock()->SetAttacked(false);
			m_eBossState = EBossState::DEATH;
			break;
		}

		// 플레이어와 몬스터 사이의 거리가 몬스터의 공격 범위보다 짧은 경우
		if (fDistance <= m_wpBoss.lock()->GetAttackRange())
		{
			m_fSumChaseSeconds = 0.0f;

			if (m_ePreAttackState == EBossState::ATTACK_01)
			{
				m_ePreAttackState = EBossState::ATTACK_02;
				m_eBossState = EBossState::ATTACK_02;
			}
			else if (m_ePreAttackState == EBossState::ATTACK_02)
			{
				m_ePreAttackState = EBossState::ATTACK_01;
				m_eBossState = EBossState::ATTACK_01;
			}

			break;
		}

		m_fSumChaseSeconds += _fDeltaSeconds;

		// 누적 추적 시간이 최대 추적 시간보다 많은 경우
		if (m_fSumChaseSeconds > m_fMaxChaseSeconds)
		{
			m_fSumChaseSeconds = 0.0f;
			m_wpBoss.lock()->SetAttacked(false);
			m_eBossState = EBossState::END_BATTLE;
			break;
		}
	}
	break;

	case Editor::EBossState::ATTACK_01:
	case Editor::EBossState::ATTACK_02:
	case Editor::EBossState::SKILL_01_BEGIN:
	case Editor::EBossState::SKILL_01:
	case Editor::EBossState::SKILL_02:
	{
		// 체력이 0보다 작은 경우
		if (m_wpBoss.lock()->GetCurHP() <= 0.0f)
		{
			m_wpBoss.lock()->SetAttacked(false);
			m_eBossState = EBossState::DEATH;
			break;
		}
	}
	break;

	case Editor::EBossState::END_BATTLE:
	{
		// 체력이 0보다 작은 경우
		if (m_wpBoss.lock()->GetCurHP() <= 0.0f)
		{
			m_wpBoss.lock()->SetAttacked(false);
			m_eBossState = EBossState::DEATH;
			break;
		}
	}
	break;

	case Editor::EBossState::DEATH:
		break;
	}
}

void Editor::COmegaStateComponent::UpdateBossBehavior(float _fDeltaSeconds)
{
	switch (m_eBossState)
	{
	case Editor::EBossState::WANDER:
	{
		Vector3 vBossPosition = m_wpBoss.lock()->GetActorWorldPosition().value();
		Vector3 vLookPosition = vBossPosition + m_wpBoss.lock()->GetWanderDirection();
		m_wpBoss.lock()->LookAt(vLookPosition);

		Vector3 vTargetPosition = vBossPosition + m_wpBoss.lock()->GetWanderDirection() * _fDeltaSeconds * m_wpBoss.lock()->GetCurMoveSpeed();

		Vector3 vOutWorldPosition = Vector3::Zero;

		if (!m_wpBoss.lock()->GetNavigationComponent()->IsValidCell(vTargetPosition, vOutWorldPosition))
		{
			Vector3 vFrom = { -1.0f, 0.0f, -1.0f };
			Vector3 vTo = { 1.0f, 0.0f, 1.0f };
			Vector3 vDirection = CMathUtility::GetRandomDirection(vFrom, vTo);
			m_wpBoss.lock()->SetWanderDirection(vDirection);
			m_eBossState = EBossState::WAIT;
			break;
		}

		m_wpBoss.lock()->SetActorLocalPosition(vOutWorldPosition);
	}
	break;

	case Editor::EBossState::CHASE:
	{
		Vector3 vSurvivorPosition = m_wpGameManager.lock()->GetSurvivor()->GetActorWorldPosition().value();
		m_wpBoss.lock()->LookAt(vSurvivorPosition);

		Vector3 vForward = m_wpBoss.lock()->GetActorWorldForwardVector().value();
		Vector3 vWildAnimalPosition = m_wpBoss.lock()->GetActorWorldPosition().value();

		Vector3 vTargetPosition = vWildAnimalPosition + vForward * _fDeltaSeconds * m_wpBoss.lock()->GetCurMoveSpeed();

		Vector3 vOutWorldPosition = Vector3::Zero;
		if (!m_wpBoss.lock()->GetNavigationComponent()->IsValidCell(vTargetPosition, vOutWorldPosition)) { break; }

		m_wpBoss.lock()->SetActorLocalPosition(vOutWorldPosition);
	}
	break;

	case Editor::EBossState::ATTACK_01:
	case Editor::EBossState::ATTACK_02:
	{
		Vector3 vPosition = m_wpGameManager.lock()->GetSurvivor()->GetActorWorldPosition().value();
		m_wpBoss.lock()->LookAt(vPosition);
	}
	break;

	case Editor::EBossState::END_BATTLE:
		break;

	case Editor::EBossState::DEATH:
		break;
	}
}

void Editor::COmegaStateComponent::OnAnimEnter(uint32 _iAnimState, float _fRatio)
{
}

void Editor::COmegaStateComponent::OnAnimStay(uint32 _iAnimState, float _fRatio)
{
}

void Editor::COmegaStateComponent::OnAnimExit(uint32 _iAnimState, float _fRatio)
{
	switch (static_cast<EBossAnimState>(_iAnimState))
	{
	case Editor::EBossAnimState::WAIT:
		break;

	case Editor::EBossAnimState::RUN:
		break;

	case Editor::EBossAnimState::ATTACK_01:
	case Editor::EBossAnimState::ATTACK_02:
	{
		if (m_ePreAttackState == EBossState::ATTACK_01)
		{
			m_ePreAttackState = EBossState::ATTACK_02;
			m_eBossState = EBossState::ATTACK_02;
		}
		else if (m_ePreAttackState == EBossState::ATTACK_02)
		{
			m_ePreAttackState = EBossState::ATTACK_01;
			m_eBossState = EBossState::ATTACK_01;
		}

		m_iSumAttack += 1;
		if (m_iSumAttack == m_iMaxAttack)
		{
			m_iSumAttack = 0;

			if (m_ePreSkillState == EBossState::SKILL_02)
			{
				m_ePreSkillState = EBossState::SKILL_01;
				m_eBossState = EBossState::SKILL_01_BEGIN;
			}
			else if (m_ePreSkillState == EBossState::SKILL_01)
			{
				m_ePreSkillState = EBossState::SKILL_02;
				m_eBossState = EBossState::SKILL_02;
			}

			break;
		}

		Vector3 vSurvivorPosition = m_wpGameManager.lock()->GetSurvivor()->GetActorWorldPosition().value();
		Vector3 vBossPosition = m_wpBoss.lock()->GetActorWorldPosition().value();

		Vector3 vDistance = vSurvivorPosition - vBossPosition;
		float fDistance = vDistance.Length();

		// 플레이어와 몬스터 사이의 거리가 몬스터의 공격 범위보다 긴 경우
		if (fDistance > m_wpBoss.lock()->GetAttackRange())
		{
			m_eBossState = EBossState::CHASE;
			break;
		}
	}
	break;

	case Editor::EBossAnimState::SKILL_01_BEGIN:
		m_eBossState = EBossState::SKILL_01;
		break;

	case Editor::EBossAnimState::SKILL_01:
		m_eBossState = EBossState::CHASE;
		break;

	case Editor::EBossAnimState::SKILL_01_END:
		break;

	case Editor::EBossAnimState::SKILL_02_BEGIN:
		break;

	case Editor::EBossAnimState::SKILL_02:
		m_eBossState = EBossState::CHASE;
		break;

	case Editor::EBossAnimState::SKILL_02_END:
		break;

	case Editor::EBossAnimState::END_BATTLE:
		m_eBossState = EBossState::WAIT;
		break;

	case Editor::EBossAnimState::DEATH:
		break;

	case Editor::EBossAnimState::ENUM_END:
		break;

	default:
		break;
	}
}
