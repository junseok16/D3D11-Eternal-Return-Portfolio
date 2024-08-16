#include "pch.h"
#include "BoarStateComponent.h"

#include "NavigationComponent.h"

#include "Survivor.h"
#include "WildAnimal.h"

#include "GameManager.h"

HRESULT Editor::CBoarStateComponent::PreInitializeComponent()
{
	if (FAILED(CWildAnimalStateComponent::PreInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CBoarStateComponent::InitializeComponent()
{
	if (FAILED(CWildAnimalStateComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CBoarStateComponent::PostInitializeComponent()
{
	if (FAILED(CWildAnimalStateComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CBoarStateComponent::BeginPlay()
{
	if (FAILED(CWildAnimalStateComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CBoarStateComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CWildAnimalStateComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CBoarStateComponent::TickComponent(float _fDeltaSeconds)
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

int32 Editor::CBoarStateComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CWildAnimalStateComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CBoarStateComponent::EndPlay()
{
	if (FAILED(CWildAnimalStateComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CBoarStateComponent::Render()
{
	CWildAnimalStateComponent::Render();
}

void Editor::CBoarStateComponent::Release()
{
	CWildAnimalStateComponent::Release();
}

void Editor::CBoarStateComponent::UpdateWildAnimalState(float _fDeltaSeconds)
{
	// ���� Ÿ���� ������Ʈ�մϴ�.
	m_eDayType = m_wpGameManager.lock()->GetDayType();

	Vector3 vSurvivorPosition = m_wpGameManager.lock()->GetSurvivor()->GetActorWorldPosition().value();
	Vector3 vWildAnimalPosition = m_wpWildAnimal.lock()->GetActorWorldPosition().value();

	Vector3 vDistance = vSurvivorPosition - vWildAnimalPosition;
	float fDistance = vDistance.Length();

	switch (m_eWildAnimalState)
	{
	case Editor::EWildAnimalState::SLEEP_BEGIN:
	{
		// ü���� 0���� ���� ���
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}
	}
	break;

	case Editor::EWildAnimalState::SLEEP:
	{
		// ü���� 0���� ���� ���
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}

		switch (m_eWildAnimalHabitType)
		{
		case Editor::EWildAnimalHabitType::DIURNAL:
			break;

		case Editor::EWildAnimalHabitType::NOCTURNAL:
		{
			// ���� �� ���
			if (m_eDayType == EDayType::NIGHT)
			{
				m_eWildAnimalState = EWildAnimalState::WAIT;
				break;
			}

			// �÷��̾�� ���� ������ �Ÿ��� ������ ��� �Ÿ����� ����� ���
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

	case Editor::EWildAnimalState::WAKE:
	{
		// ü���� 0���� ���� ���
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}
	}
	break;

	case Editor::EWildAnimalState::WAIT:
	{
		// ü���� 0���� ���� ���
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}

		// �÷��̾�� ���� ������ �Ÿ��� ������ ��� �Ÿ����� ����� ���
		if (fDistance <= m_wpWildAnimal.lock()->GetBewareDistance())
		{
			m_eWildAnimalState = EWildAnimalState::BEWARE_BEGIN;
			break;
		}

		// ���༺�� ���
		if (m_eWildAnimalHabitType == EWildAnimalHabitType::NOCTURNAL)
		{
			// ���� ���
			if (m_eDayType == EDayType::DAY)
			{
				m_eWildAnimalState = EWildAnimalState::SLEEP_BEGIN;
				break;
			}
		}

		// ���Ͱ� ���ݴ��� ���
		if (m_wpWildAnimal.lock()->IsAttacked())
		{
			// �÷��̾�� ���� ������ �Ÿ��� ������ ���� �������� �� ���
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

	case Editor::EWildAnimalState::BEWARE_BEGIN:
	{
		// ü���� 0���� ���� ���
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}
	}
	break;

	case Editor::EWildAnimalState::BEWARE:
	{
		// ü���� 0���� ���� ���
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}

		// �÷��̾�� ���� ������ �Ÿ��� ������ ��� �Ÿ����� �� ���
		if (fDistance > m_wpWildAnimal.lock()->GetBewareDistance())
		{
			m_eWildAnimalState = EWildAnimalState::BEWARE_END;
			break;
		}

		// ���Ͱ� ���ݴ��� ���
		if (m_wpWildAnimal.lock()->IsAttacked())
		{
			// �÷��̾�� ���� ������ �Ÿ��� ������ ���� �������� �� ���
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

	case Editor::EWildAnimalState::BEWARE_END:
	{
		// ü���� 0���� ���� ���
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}
	}
	break;

	case Editor::EWildAnimalState::ATTACK_01:
	case Editor::EWildAnimalState::ATTACK_02:
	{
		// ü���� 0���� ���� ���
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_wpWildAnimal.lock()->SetAttacked(false);
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}

		/*
		// �÷��̾�� ���� ������ �Ÿ��� ������ ���� �������� �� ���
		if (fDistance > m_wpWildAnimal.lock()->GetAttackRange())
		{
			m_eWildAnimalState = EWildAnimalState::CHASE;
			break;
		}
		*/
	}
	break;

	case Editor::EWildAnimalState::SKILL_BEGIN:
	{
		// ü���� 0���� ���� ���
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_wpWildAnimal.lock()->SetAttacked(false);
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}
	}
	break;

	case Editor::EWildAnimalState::SKILL:
	{
		// ü���� 0���� ���� ���
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_wpWildAnimal.lock()->SetAttacked(false);
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}
	}
	break;

	case Editor::EWildAnimalState::CHASE:
	{
		m_fSumChaseSeconds += _fDeltaSeconds;

		// ü���� 0���� ���� ���
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_fSumChaseSeconds = 0.0f;
			m_wpWildAnimal.lock()->SetAttacked(false);
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}

		// �÷��̾�� ���� ������ �Ÿ��� ������ ���� �������� ª�� ���
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

		// ���� ���� �ð��� �ִ� ���� �ð����� ���� ���
		if (m_fSumChaseSeconds > m_fMaxChaseSeconds)
		{
			m_fSumChaseSeconds = 0.0f;
			m_wpWildAnimal.lock()->SetAttacked(false);
			m_eWildAnimalState = EWildAnimalState::END_BATTLE;
			break;
		}
	}
	break;

	case Editor::EWildAnimalState::END_BATTLE:
	{
		// ü���� 0���� ���� ���
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_wpWildAnimal.lock()->SetAttacked(false);
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}
	}
	break;

	case Editor::EWildAnimalState::RETREAT:
	{
		// ü���� 0���� ���� ���
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_wpWildAnimal.lock()->SetAttacked(false);
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}

		Vector3 vDistance = m_wpWildAnimal.lock()->GetSpawnPosition() - m_wpWildAnimal.lock()->GetActorWorldPosition().value();
		float fDistance = vDistance.Length();

		if (fDistance <= 1.5f)
		{
			switch (m_eWildAnimalHabitType)
			{
			case Editor::EWildAnimalHabitType::DIURNAL:
				m_eWildAnimalState = EWildAnimalState::WAIT;
				break;

			case Editor::EWildAnimalHabitType::NOCTURNAL:
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

	case Editor::EWildAnimalState::DEATH:
		break;
	}
}

void Editor::CBoarStateComponent::UpdateWildAnimalBehavior(float _fDeltaSeconds)
{
	switch (m_eWildAnimalState)
	{
	case Editor::EWildAnimalState::ATTACK_01:
	case Editor::EWildAnimalState::ATTACK_02:
	{
		Vector3 vPosition = m_wpGameManager.lock()->GetSurvivor()->GetActorWorldPosition().value();
		m_wpWildAnimal.lock()->LookAt(vPosition);
	}
	break;

	case Editor::EWildAnimalState::CHASE:
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

	case Editor::EWildAnimalState::END_BATTLE:
	{

	}
	break;

	case Editor::EWildAnimalState::RETREAT:
	{
		Vector3 vLatestPosition = m_vecMementos.back();// vWildAnimalPosition + vForward * _fDeltaSeconds * m_wpWildAnimal.lock()->GetCurMoveSpeed();
		m_wpWildAnimal.lock()->LookAt(vLatestPosition);

		Vector3 vForward = m_wpWildAnimal.lock()->GetActorWorldForwardVector().value();
		Vector3 vWildAnimalPosition = m_wpWildAnimal.lock()->GetActorWorldPosition().value();

		Vector3 vDistance = vLatestPosition - vWildAnimalPosition;
		float fDistance = vDistance.Length();

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

	case Editor::EWildAnimalState::SKILL:
	{

	}
	break;

	case Editor::EWildAnimalState::DEATH:
	{

	}
	break;
	}
}

void Editor::CBoarStateComponent::OnAnimEnter(uint32 _iAnimState, float _fRatio)
{
}

void Editor::CBoarStateComponent::OnAnimStay(uint32 _iAnimState, float _fRatio)
{
}

void Editor::CBoarStateComponent::OnAnimExit(uint32 _iAnimState, float _fRatio)
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
		case Editor::EWildAnimalHabitType::DIURNAL:
			m_eWildAnimalState = EWildAnimalState::WAIT;
			break;

		case Editor::EWildAnimalHabitType::NOCTURNAL:
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
			m_eWildAnimalState = EWildAnimalState::SKILL_BEGIN;
			break;
		}

		Vector3 vSurvivorPosition = m_wpGameManager.lock()->GetSurvivor()->GetActorWorldPosition().value();
		Vector3 vWildAnimalPosition = m_wpWildAnimal.lock()->GetActorWorldPosition().value();

		Vector3 vDistance = vSurvivorPosition - vWildAnimalPosition;
		float fDistance = vDistance.Length();


		// �÷��̾�� ���� ������ �Ÿ��� ������ ���� �������� �� ���
		if (fDistance > m_wpWildAnimal.lock()->GetAttackRange())
		{
			m_eWildAnimalState = EWildAnimalState::CHASE;
			break;
		}
	}
	break;

	case EWildAnimalAnimState::SKILL_BEGIN:		m_eWildAnimalState = EWildAnimalState::SKILL;			break;

	case EWildAnimalAnimState::SKILL:			m_eWildAnimalState = EWildAnimalState::CHASE;			break;
	case EWildAnimalAnimState::END_BATTLE:		m_eWildAnimalState = EWildAnimalState::RETREAT;			break;
	case EWildAnimalAnimState::DEATH:																	break;
	case EWildAnimalAnimState::DANCE:																	break;
	default:																							break;
	}
}
