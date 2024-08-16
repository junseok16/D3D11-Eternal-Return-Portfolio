#include "pch.h"
#include "YukiStateComponent.h"

#include "InputComponent.h"

#include "Survivor.h"

HRESULT Client::CYukiStateComponent::PreInitializeComponent()
{
	if (FAILED(CSurvivorStateComponent::PreInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CYukiStateComponent::InitializeComponent()
{
	if (FAILED(CSurvivorStateComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CYukiStateComponent::PostInitializeComponent()
{
	if (FAILED(CSurvivorStateComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CYukiStateComponent::BeginPlay()
{
	if (FAILED(CSurvivorStateComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CYukiStateComponent::PreTickComponent(float _fDeltaSeconds)
{
	UpdateSurvivorState(_fDeltaSeconds);

	return CSurvivorStateComponent::PreTickComponent(_fDeltaSeconds);
}

int32 Client::CYukiStateComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CStateComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Client::CYukiStateComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CStateComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

HRESULT Client::CYukiStateComponent::EndPlay()
{
	if (FAILED(CStateComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CYukiStateComponent::Render()
{
	CStateComponent::Render();
}

void Client::CYukiStateComponent::Release()
{
	CStateComponent::Release();
}

void Client::CYukiStateComponent::UpdateSurvivorState(float _fDeltaSeconds)
{
	switch (m_eSurvivorState)
	{
	case Client::ESurvivorState::WAIT:
	{
		// ���� Ű�� ���� ���
		if (m_wpInputComponent.lock()->IsKeyPressed(DIK_W)
			|| m_wpInputComponent.lock()->IsKeyPressed(DIK_S)
			|| m_wpInputComponent.lock()->IsKeyPressed(DIK_D)
			|| m_wpInputComponent.lock()->IsKeyPressed(DIK_A))
		{
			m_eSurvivorState = ESurvivorState::RUN;
			break;
		}

		// ��Ŭ���� ���� ���
		if (m_wpInputComponent.lock()->IsMouseDown(EMouseActionType::RIGHT_BUTTON))
		{
			if (m_ePreAttackState == ESurvivorState::ATTACK_01)
			{
				m_ePreAttackState = ESurvivorState::ATTACK_02;
				m_eSurvivorState = ESurvivorState::ATTACK_02;
			}
			else if (m_ePreAttackState == ESurvivorState::ATTACK_02)
			{
				m_ePreAttackState = ESurvivorState::ATTACK_01;
				m_eSurvivorState = ESurvivorState::ATTACK_01;
			}
			break;
		}

		// 1�� Ű�� ���� ���
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_1))
		{
			float fStaminaConsumption = m_wpSurvivor.lock()->GetStaminaConsumption(ESkillType::FIRST);

			if (fStaminaConsumption <= m_wpSurvivor.lock()->GetCurSP())
			{
				m_wpSurvivor.lock()->AddCurSP(-fStaminaConsumption);
				m_eSurvivorState = ESurvivorState::SKILL_01;
				break;
			}
		}
		
		// 2�� Ű�� ���� ���
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_2))
		{
			float fStaminaConsumption = m_wpSurvivor.lock()->GetStaminaConsumption(ESkillType::SECOND);

			if (fStaminaConsumption <= m_wpSurvivor.lock()->GetCurSP())
			{
				m_wpSurvivor.lock()->AddCurSP(-fStaminaConsumption);
				m_eSurvivorState = ESurvivorState::SKILL_02;
				break;
			}
		}
		
		// 3�� Ű�� ���� ���
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_3))
		{
			float fStaminaConsumption = m_wpSurvivor.lock()->GetStaminaConsumption(ESkillType::THIRD);

			if (fStaminaConsumption <= m_wpSurvivor.lock()->GetCurSP())
			{
				m_wpSurvivor.lock()->AddCurSP(-fStaminaConsumption);
				m_eSurvivorState = ESurvivorState::SKILL_03_BEGIN;
				break;
			}
		}

		// 4�� Ű�� ���� ���
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_4))
		{
			float fStaminaConsumption = m_wpSurvivor.lock()->GetStaminaConsumption(ESkillType::FOURTH);

			if (fStaminaConsumption <= m_wpSurvivor.lock()->GetCurSP())
			{
				m_wpSurvivor.lock()->AddCurSP(-fStaminaConsumption);
				m_eSurvivorState = ESurvivorState::SKILL_04_BEGIN;
				break;
			}
		}

		// E Ű�� ���� ���
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_E))
		{
			switch (m_wpSurvivor.lock()->GetCurCollectibleType())
			{
			case ECollectibleType::STONE:	m_eSurvivorState = ESurvivorState::COLLECT_STONE;		break;
			case ECollectibleType::BRANCH:	m_eSurvivorState = ESurvivorState::COLLECT_WOOD;		break;
			case ECollectibleType::WATER:	m_eSurvivorState = ESurvivorState::COLLECT_WATER;		break;
			case ECollectibleType::POTATO:	/* m_eSurvivorState = ESurvivorState::COLLECT_WOOD;*/	break;
			}

			switch (m_wpSurvivor.lock()->GetCurConsoleType())
			{
			case EConsoleType::HYPERLOOP:
			case EConsoleType::SECURITY_CONSOLE:	m_eSurvivorState = ESurvivorState::OPERATE;	break;
			}
		}

		// C Ű�� ���� ���
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_C))
		{
			m_eSurvivorState = ESurvivorState::CRAFT_METAL;
			break;
		}

		// V Ű�� ���� ���
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_V))
		{
			m_eSurvivorState = ESurvivorState::CRAFT_FOOD;
			break;
		}

		// X Ű�� ���� ���
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_X))
		{
			m_eSurvivorState = ESurvivorState::REST_BEGIN;
			break;
		}

		// ü���� 0���� ���� ���
		if (m_wpSurvivor.lock()->GetCurHP() <= 0)
		{
			m_eSurvivorState = ESurvivorState::DEATH;
			break;
		}
	}
	break;

	case Client::ESurvivorState::RUN:
	{
		// ���� Ű�� ������ ���� ���
		if (!m_wpInputComponent.lock()->IsKeyPressed(DIK_W)
			&& !m_wpInputComponent.lock()->IsKeyPressed(DIK_S)
			&& !m_wpInputComponent.lock()->IsKeyPressed(DIK_D)
			&& !m_wpInputComponent.lock()->IsKeyPressed(DIK_A))
		{
			m_eSurvivorState = ESurvivorState::WAIT;
			break;
		}

		// ��Ŭ���� ���� ���
		if (m_wpInputComponent.lock()->IsMouseDown(EMouseActionType::RIGHT_BUTTON))
		{
			if (m_ePreAttackState == ESurvivorState::ATTACK_01)
			{
				m_ePreAttackState = ESurvivorState::ATTACK_02;
				m_eSurvivorState = ESurvivorState::ATTACK_02;
			}
			else if (m_ePreAttackState == ESurvivorState::ATTACK_02)
			{
				m_ePreAttackState = ESurvivorState::ATTACK_01;
				m_eSurvivorState = ESurvivorState::ATTACK_01;
			}
			break;
		}

		// 1�� Ű�� ���� ���
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_1))
		{
			float fStaminaConsumption = m_wpSurvivor.lock()->GetStaminaConsumption(ESkillType::FIRST);

			if (fStaminaConsumption <= m_wpSurvivor.lock()->GetCurSP())
			{
				m_wpSurvivor.lock()->AddCurSP(-fStaminaConsumption);
				m_eSurvivorState = ESurvivorState::SKILL_01;
				break;
			}
		}

		// 2�� Ű�� ���� ���
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_2))
		{
			float fStaminaConsumption = m_wpSurvivor.lock()->GetStaminaConsumption(ESkillType::SECOND);

			if (fStaminaConsumption <= m_wpSurvivor.lock()->GetCurSP())
			{
				m_wpSurvivor.lock()->AddCurSP(-fStaminaConsumption);
				m_eSurvivorState = ESurvivorState::SKILL_02;
				break;
			}
		}

		// 3�� Ű�� ���� ���
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_3))
		{
			float fStaminaConsumption = m_wpSurvivor.lock()->GetStaminaConsumption(ESkillType::THIRD);

			if (fStaminaConsumption <= m_wpSurvivor.lock()->GetCurSP())
			{
				m_wpSurvivor.lock()->AddCurSP(-fStaminaConsumption);
				m_eSurvivorState = ESurvivorState::SKILL_03_BEGIN;
				break;
			}
		}

		// 4�� Ű�� ���� ���
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_4))
		{
			float fStaminaConsumption = m_wpSurvivor.lock()->GetStaminaConsumption(ESkillType::FOURTH);

			if (fStaminaConsumption <= m_wpSurvivor.lock()->GetCurSP())
			{
				m_wpSurvivor.lock()->AddCurSP(-fStaminaConsumption);
				m_eSurvivorState = ESurvivorState::SKILL_04_BEGIN;
				break;
			}
		}

		// X Ű�� ���� ���
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_X))
		{
			m_eSurvivorState = ESurvivorState::REST_BEGIN;
			break;
		}

		// ü���� 0���� ���� ���
		if (m_wpSurvivor.lock()->GetCurHP() <= 0)
		{
			m_eSurvivorState = ESurvivorState::DEATH;
			break;
		}
	}
	break;

	case Client::ESurvivorState::ATTACK_01:
	case Client::ESurvivorState::ATTACK_02:
	{
		// 1�� Ű�� ���� ���
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_1))
		{
			float fStaminaConsumption = m_wpSurvivor.lock()->GetStaminaConsumption(ESkillType::FIRST);

			if (fStaminaConsumption <= m_wpSurvivor.lock()->GetCurSP())
			{
				m_wpSurvivor.lock()->AddCurSP(-fStaminaConsumption);
				m_eSurvivorState = ESurvivorState::SKILL_01;
				break;
			}
		}

		// 2�� Ű�� ���� ���
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_2))
		{
			float fStaminaConsumption = m_wpSurvivor.lock()->GetStaminaConsumption(ESkillType::SECOND);

			if (fStaminaConsumption <= m_wpSurvivor.lock()->GetCurSP())
			{
				m_wpSurvivor.lock()->AddCurSP(-fStaminaConsumption);
				m_eSurvivorState = ESurvivorState::SKILL_02;
				break;
			}
		}

		// 3�� Ű�� ���� ���
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_3))
		{
			float fStaminaConsumption = m_wpSurvivor.lock()->GetStaminaConsumption(ESkillType::THIRD);

			if (fStaminaConsumption <= m_wpSurvivor.lock()->GetCurSP())
			{
				m_wpSurvivor.lock()->AddCurSP(-fStaminaConsumption);
				m_eSurvivorState = ESurvivorState::SKILL_03_BEGIN;
				break;
			}
		}

		// 4�� Ű�� ���� ���
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_4))
		{
			float fStaminaConsumption = m_wpSurvivor.lock()->GetStaminaConsumption(ESkillType::FOURTH);

			if (fStaminaConsumption <= m_wpSurvivor.lock()->GetCurSP())
			{
				m_wpSurvivor.lock()->AddCurSP(-fStaminaConsumption);
				m_eSurvivorState = ESurvivorState::SKILL_04_BEGIN;
				break;
			}
		}

		// ü���� 0���� ���� ���
		if (m_wpSurvivor.lock()->GetCurHP() <= 0)
		{
			m_eSurvivorState = ESurvivorState::DEATH;
			break;
		}
	}
	break;

	case Client::ESurvivorState::SKILL_01:
	{
		// ü���� 0���� ���� ���
		if (m_wpSurvivor.lock()->GetCurHP() <= 0)
		{
			m_eSurvivorState = ESurvivorState::DEATH;
			break;
		}
	}
	break;

	case Client::ESurvivorState::SKILL_02:
	{
		// ü���� 0���� ���� ���
		if (m_wpSurvivor.lock()->GetCurHP() <= 0)
		{
			m_eSurvivorState = ESurvivorState::DEATH;
			break;
		}
	}
	break;

	case Client::ESurvivorState::SKILL_03_BEGIN:
	case Client::ESurvivorState::SKILL_03:
	case Client::ESurvivorState::SKILL_03_END:
	{
		// ü���� 0���� ���� ���
		if (m_wpSurvivor.lock()->GetCurHP() <= 0)
		{
			m_eSurvivorState = ESurvivorState::DEATH;
			break;
		}
	}
	break;

	case Client::ESurvivorState::SKILL_04_BEGIN:
	{
		// ü���� 0���� ���� ���
		if (m_wpSurvivor.lock()->GetCurHP() <= 0)
		{
			m_eSurvivorState = ESurvivorState::DEATH;
			break;
		}
	}
	break;

	case Client::ESurvivorState::SKILL_04_END:
	{
		// ü���� 0���� ���� ���
		if (m_wpSurvivor.lock()->GetCurHP() <= 0)
		{
			m_eSurvivorState = ESurvivorState::DEATH;
			break;
		}
	}
	break;

	case Client::ESurvivorState::COLLECT_STONE:
	{
		m_fSumCollectStoneSeconds += _fDeltaSeconds;
	}
	break;

	case Client::ESurvivorState::COLLECT_WOOD:
	{
		m_fSumCollectBranchSeconds += _fDeltaSeconds;
	}
	break;

	case Client::ESurvivorState::COLLECT_WATER:
	{
		m_fSumCollectWaterSeconds += _fDeltaSeconds;
	}
	break;

	case Client::ESurvivorState::CRAFT_FOOD:
	case Client::ESurvivorState::CRAFT_METAL:
	{
		// Esc Ű�� ���� ���
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_ESCAPE))
		{
			m_eSurvivorState = ESurvivorState::WAIT;
			break;
		}
	}
	break;

	case Client::ESurvivorState::OPERATE:
	{
		m_fSumOperateSeconds += _fDeltaSeconds;

		// Esc Ű�� ���� ���
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_ESCAPE))
		{
			m_fSumOperateSeconds = 0.0f;
			m_eSurvivorState = ESurvivorState::WAIT;
			break;
		}
	}
	break;

	case Client::ESurvivorState::DEATH:
	{

	}
	break;

	case Client::ESurvivorState::REST_BEGIN:
	{

	}
	break;

	case Client::ESurvivorState::REST:
	{
		m_fSumRestSeconds += _fDeltaSeconds;

		if (m_wpInputComponent.lock()->IsKeyDown(DIK_W)
			|| m_wpInputComponent.lock()->IsKeyDown(DIK_S)
			|| m_wpInputComponent.lock()->IsKeyDown(DIK_D)
			|| m_wpInputComponent.lock()->IsKeyDown(DIK_A)
			|| m_wpInputComponent.lock()->IsKeyDown(DIK_ESCAPE))
		{
			m_fSumRestSeconds = 0.0f;
			m_eSurvivorState = ESurvivorState::REST_END;
			break;
		}

		if (0.5f <= m_fSumRestSeconds)
		{
			m_fSumRestSeconds = 0.0f;
			float fHPRegeneration = m_wpSurvivor.lock()->GetHPRegeneration();
			float fSPRegeneration = m_wpSurvivor.lock()->GetSPRegeneration();

			m_wpSurvivor.lock()->AddCurHP(10 * fHPRegeneration);
			m_wpSurvivor.lock()->AddCurSP(10 * fSPRegeneration);
		}
	}
	break;

	case Client::ESurvivorState::REST_END:
	{

	}
	break;
	}
}

void Client::CYukiStateComponent::OnAnimEnter(uint32 _iAnimState, float _fRatio)
{
}

void Client::CYukiStateComponent::OnAnimStay(uint32 _iAnimState, float _fRatio)
{
}

void Client::CYukiStateComponent::OnAnimExit(uint32 _iAnimState, float _fRatio)
{
	switch (static_cast<ESurvivorAnimState>(_iAnimState))
	{
	case ESurvivorAnimState::ATTACK_01:
	case ESurvivorAnimState::ATTACK_02:
	case ESurvivorAnimState::SKILL_01:
	case ESurvivorAnimState::SKILL_02:
	case ESurvivorAnimState::SKILL_03_BEGIN:
	case ESurvivorAnimState::SKILL_03:
	case ESurvivorAnimState::SKILL_03_END:
	case ESurvivorAnimState::SKILL_04_BEGIN:
	case ESurvivorAnimState::SKILL_04:
	case ESurvivorAnimState::SKILL_04_END:
	case ESurvivorAnimState::REST_END:
		m_eSurvivorState = ESurvivorState::WAIT;
		break;

	case ESurvivorAnimState::REST_BEGIN:
		m_eSurvivorState = ESurvivorState::REST;
		break;

	default:
		break;
	}
}
