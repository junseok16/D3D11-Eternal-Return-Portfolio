#include "pch.h"
#include "YukiStateComponent.h"

#include "InputComponent.h"

#include "Survivor.h"

HRESULT Editor::CYukiStateComponent::PreInitializeComponent()
{
	if (FAILED(CSurvivorStateComponent::PreInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CYukiStateComponent::InitializeComponent()
{
	if (FAILED(CSurvivorStateComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CYukiStateComponent::PostInitializeComponent()
{
	if (FAILED(CSurvivorStateComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CYukiStateComponent::BeginPlay()
{
	if (FAILED(CSurvivorStateComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CYukiStateComponent::PreTickComponent(float _fDeltaSeconds)
{
	UpdateSurvivorState(_fDeltaSeconds);

	return CSurvivorStateComponent::PreTickComponent(_fDeltaSeconds);
}

int32 Editor::CYukiStateComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CStateComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Editor::CYukiStateComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CStateComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

HRESULT Editor::CYukiStateComponent::EndPlay()
{
	if (FAILED(CStateComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CYukiStateComponent::Render()
{
	CStateComponent::Render();
}

void Editor::CYukiStateComponent::Release()
{
	CStateComponent::Release();
}

void Editor::CYukiStateComponent::UpdateSurvivorState(float _fDeltaSeconds)
{
	switch (m_eSurvivorState)
	{
	case Editor::ESurvivorState::WAIT:
	{
		// 방향 키를 누른 경우
		if (m_wpInputComponent.lock()->IsKeyPressed(DIK_W)
			|| m_wpInputComponent.lock()->IsKeyPressed(DIK_S)
			|| m_wpInputComponent.lock()->IsKeyPressed(DIK_D)
			|| m_wpInputComponent.lock()->IsKeyPressed(DIK_A))
		{
			m_eSurvivorState = ESurvivorState::RUN;
			break;
		}

		// 우클릭을 누른 경우
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

		// 1번 키를 누른 경우
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
		
		// 2번 키를 누른 경우
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
		
		// 3번 키를 누른 경우
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

		// 4번 키를 누른 경우
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

		// E 키를 누른 경우
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

		// C 키를 누른 경우
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_C))
		{
			m_eSurvivorState = ESurvivorState::CRAFT_METAL;
			break;
		}

		// V 키를 누른 경우
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_V))
		{
			m_eSurvivorState = ESurvivorState::CRAFT_FOOD;
			break;
		}

		// X 키를 누른 경우
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_X))
		{
			m_eSurvivorState = ESurvivorState::REST_BEGIN;
			break;
		}

		// 체력이 0보다 작은 경우
		if (m_wpSurvivor.lock()->GetCurHP() <= 0)
		{
			m_eSurvivorState = ESurvivorState::DEATH;
			break;
		}
	}
	break;

	case Editor::ESurvivorState::RUN:
	{
		// 방향 키를 누르지 않은 경우
		if (!m_wpInputComponent.lock()->IsKeyPressed(DIK_W)
			&& !m_wpInputComponent.lock()->IsKeyPressed(DIK_S)
			&& !m_wpInputComponent.lock()->IsKeyPressed(DIK_D)
			&& !m_wpInputComponent.lock()->IsKeyPressed(DIK_A))
		{
			m_eSurvivorState = ESurvivorState::WAIT;
			break;
		}

		// 우클릭을 누른 경우
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

		// 1번 키를 누른 경우
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

		// 2번 키를 누른 경우
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

		// 3번 키를 누른 경우
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

		// 4번 키를 누른 경우
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

		// X 키를 누른 경우
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_X))
		{
			m_eSurvivorState = ESurvivorState::REST_BEGIN;
			break;
		}

		// 체력이 0보다 작은 경우
		if (m_wpSurvivor.lock()->GetCurHP() <= 0)
		{
			m_eSurvivorState = ESurvivorState::DEATH;
			break;
		}
	}
	break;

	case Editor::ESurvivorState::ATTACK_01:
	case Editor::ESurvivorState::ATTACK_02:
	{
		// 1번 키를 누른 경우
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

		// 2번 키를 누른 경우
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

		// 3번 키를 누른 경우
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

		// 4번 키를 누른 경우
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

		// 체력이 0보다 작은 경우
		if (m_wpSurvivor.lock()->GetCurHP() <= 0)
		{
			m_eSurvivorState = ESurvivorState::DEATH;
			break;
		}
	}
	break;

	case Editor::ESurvivorState::SKILL_01:
	{
		// 체력이 0보다 작은 경우
		if (m_wpSurvivor.lock()->GetCurHP() <= 0)
		{
			m_eSurvivorState = ESurvivorState::DEATH;
			break;
		}
	}
	break;

	case Editor::ESurvivorState::SKILL_02:
	{
		// 체력이 0보다 작은 경우
		if (m_wpSurvivor.lock()->GetCurHP() <= 0)
		{
			m_eSurvivorState = ESurvivorState::DEATH;
			break;
		}
	}
	break;

	case Editor::ESurvivorState::SKILL_03_BEGIN:
	case Editor::ESurvivorState::SKILL_03:
	case Editor::ESurvivorState::SKILL_03_END:
	{
		// 체력이 0보다 작은 경우
		if (m_wpSurvivor.lock()->GetCurHP() <= 0)
		{
			m_eSurvivorState = ESurvivorState::DEATH;
			break;
		}
	}
	break;

	case Editor::ESurvivorState::SKILL_04_BEGIN:
	{
		// 체력이 0보다 작은 경우
		if (m_wpSurvivor.lock()->GetCurHP() <= 0)
		{
			m_eSurvivorState = ESurvivorState::DEATH;
			break;
		}
	}
	break;

	case Editor::ESurvivorState::SKILL_04_END:
	{
		// 체력이 0보다 작은 경우
		if (m_wpSurvivor.lock()->GetCurHP() <= 0)
		{
			m_eSurvivorState = ESurvivorState::DEATH;
			break;
		}
	}
	break;

	case Editor::ESurvivorState::COLLECT_STONE:
	{
		m_fSumCollectStoneSeconds += _fDeltaSeconds;
	}
	break;

	case Editor::ESurvivorState::COLLECT_WOOD:
	{
		m_fSumCollectBranchSeconds += _fDeltaSeconds;
	}
	break;

	case Editor::ESurvivorState::COLLECT_WATER:
	{
		m_fSumCollectWaterSeconds += _fDeltaSeconds;
	}
	break;

	case Editor::ESurvivorState::CRAFT_FOOD:
	case Editor::ESurvivorState::CRAFT_METAL:
	{
		// Esc 키를 누른 경우
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_ESCAPE))
		{
			m_eSurvivorState = ESurvivorState::WAIT;
			break;
		}
	}
	break;

	case Editor::ESurvivorState::OPERATE:
	{
		m_fSumOperateSeconds += _fDeltaSeconds;

		// Esc 키를 누른 경우
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_ESCAPE))
		{
			m_fSumOperateSeconds = 0.0f;
			m_eSurvivorState = ESurvivorState::WAIT;
			break;
		}
	}
	break;

	case Editor::ESurvivorState::DEATH:
	{

	}
	break;

	case Editor::ESurvivorState::REST_BEGIN:
	{

	}
	break;

	case Editor::ESurvivorState::REST:
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

	case Editor::ESurvivorState::REST_END:
	{

	}
	break;
	}
}

void Editor::CYukiStateComponent::OnAnimEnter(uint32 _iAnimState, float _fRatio)
{
}

void Editor::CYukiStateComponent::OnAnimStay(uint32 _iAnimState, float _fRatio)
{
}

void Editor::CYukiStateComponent::OnAnimExit(uint32 _iAnimState, float _fRatio)
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
