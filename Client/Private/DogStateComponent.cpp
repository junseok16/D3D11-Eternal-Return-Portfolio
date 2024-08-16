#include "pch.h"
#include "DogStateComponent.h"

#include "NavigationComponent.h"
#include "Survivor.h"
#include "WildAnimal.h"

#include "GameManager.h"

HRESULT Client::CDogStateComponent::PreInitializeComponent()
{
	if (FAILED(CWildAnimalStateComponent::PreInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CDogStateComponent::InitializeComponent()
{
	if (FAILED(CWildAnimalStateComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CDogStateComponent::PostInitializeComponent()
{
	if (FAILED(CWildAnimalStateComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CDogStateComponent::BeginPlay()
{
	if (FAILED(CWildAnimalStateComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CDogStateComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CWildAnimalStateComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CDogStateComponent::TickComponent(float _fDeltaSeconds)
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

int32 Client::CDogStateComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CWildAnimalStateComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CDogStateComponent::EndPlay()
{
	if (FAILED(CWildAnimalStateComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CDogStateComponent::Render()
{
	CWildAnimalStateComponent::Render();
}

void Client::CDogStateComponent::Release()
{
	CWildAnimalStateComponent::Release();
}

void Client::CDogStateComponent::UpdateWildAnimalState(float _fDeltaSeconds)
{
	// ���� Ÿ���� ������Ʈ�մϴ�.
	m_eDayType = m_wpGameManager.lock()->GetDayType();

	Vector3 vSurvivorPosition = m_wpGameManager.lock()->GetSurvivor()->GetActorWorldPosition().value();
	Vector3 vWildAnimalPosition = m_wpWildAnimal.lock()->GetActorWorldPosition().value();

	Vector3 vDistance = vSurvivorPosition - vWildAnimalPosition;
	float fDistance = vDistance.Length();

	switch (m_eWildAnimalState)
	{
	case Client::EWildAnimalState::SLEEP_BEGIN:
	{
		// ü���� 0���� ���� ���
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}
	}
	break;

	case Client::EWildAnimalState::SLEEP:
	{
		// ü���� 0���� ���� ���
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}

		switch (m_eWildAnimalHabitType)
		{
		case Client::EWildAnimalHabitType::DIURNAL:
			break;

		case Client::EWildAnimalHabitType::NOCTURNAL:
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

	case Client::EWildAnimalState::WAKE:
	{
		// ü���� 0���� ���� ���
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}
	}
	break;

	case Client::EWildAnimalState::WAIT:
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

	case Client::EWildAnimalState::BEWARE_BEGIN:
	{
		// ü���� 0���� ���� ���
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}
	}
	break;

	case Client::EWildAnimalState::BEWARE:
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

	case Client::EWildAnimalState::BEWARE_END:
	{
		// ü���� 0���� ���� ���
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
		// ü���� 0���� ���� ���
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

	case Client::EWildAnimalState::END_BATTLE:
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

	case Client::EWildAnimalState::RETREAT:
	{
		// m_wpWildAnimal.lock()->SetAttacked(false);

		// ü���� 0���� ���� ���
		if (m_wpWildAnimal.lock()->GetCurHP() <= 0.0f)
		{
			m_eWildAnimalState = EWildAnimalState::DEATH;
			break;
		}

		Vector3 vDistance = m_wpWildAnimal.lock()->GetSpawnPosition() - m_wpWildAnimal.lock()->GetActorWorldPosition().value();
		if (vDistance.Length() <= 1.5f)
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
		// TODO; ������ �ð�
	}
	break;
	}
}

void Client::CDogStateComponent::UpdateWildAnimalBehavior(float _fDeltaSeconds)
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

	case Client::EWildAnimalState::DEATH:
		break;
	}
}

void Client::CDogStateComponent::OnAnimEnter(uint32 _iAnimState, float _fRatio)
{
}

void Client::CDogStateComponent::OnAnimStay(uint32 _iAnimState, float _fRatio)
{
}

void Client::CDogStateComponent::OnAnimExit(uint32 _iAnimState, float _fRatio)
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
	case EWildAnimalAnimState::END_BATTLE:		m_eWildAnimalState = EWildAnimalState::RETREAT;			break;
	case EWildAnimalAnimState::DEATH:																	break;
	case EWildAnimalAnimState::DANCE:																	break;
	default:																							break;
	}
}
