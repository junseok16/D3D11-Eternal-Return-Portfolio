#include "pch.h"
#include "HyunwooStateComponent.h"

// component
#include "InputComponent.h"
#include "CameraComponent.h"

// survivor
#include "Survivor.h"
#include "ItemBox.h"
#include "Inventory.h"
#include "WildAnimal.h"

HRESULT Editor::CHyunwooStateComponent::PreInitializeComponent()
{
	if (FAILED(CSurvivorStateComponent::PreInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CHyunwooStateComponent::InitializeComponent()
{
	if (FAILED(CSurvivorStateComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CHyunwooStateComponent::PostInitializeComponent()
{
	if (FAILED(CSurvivorStateComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CHyunwooStateComponent::BeginPlay()
{
	if (FAILED(CSurvivorStateComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CHyunwooStateComponent::PreTickComponent(float _fDeltaSeconds)
{
	UpdateSurvivorState(_fDeltaSeconds);

	return CSurvivorStateComponent::PreTickComponent(_fDeltaSeconds);
}

int32 Editor::CHyunwooStateComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CStateComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Editor::CHyunwooStateComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CStateComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

HRESULT Editor::CHyunwooStateComponent::EndPlay()
{
	if (FAILED(CStateComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CHyunwooStateComponent::Render()
{
	CStateComponent::Render();
}

void Editor::CHyunwooStateComponent::Release()
{
	CStateComponent::Release();
}

void Editor::CHyunwooStateComponent::UpdateSurvivorState(float _fDeltaSeconds)
{
	switch (m_eSurvivorState)
	{
	case Editor::ESurvivorState::WAIT:
	{
		// 1 ~ 8번 키를 누른 경우
		EatItem();

		// 방향 키를 누른 경우
		if (m_wpInputComponent.lock()->IsKeyPressed(DIK_W)
			|| m_wpInputComponent.lock()->IsKeyPressed(DIK_S)
			|| m_wpInputComponent.lock()->IsKeyPressed(DIK_D)
			|| m_wpInputComponent.lock()->IsKeyPressed(DIK_A))
		{
			if (m_bItemBoxOpen) { break; }

			m_eSurvivorState = ESurvivorState::RUN;
			break;
		}

		// 좌클릭을 누른 경우
		if (m_wpInputComponent.lock()->IsMouseDown(EMouseActionType::LEFT_BUTTON))
		{
			if (m_bItemBoxOpen) { break; }

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

		// SHIFT 키를 누른 경우
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_LSHIFT))
		{
			if (m_bItemBoxOpen) { break; }

			if (m_wpSurvivor.lock()->IsSkillValid(ESkillType::FIRST))
			{
				m_eSurvivorState = ESurvivorState::SKILL_01;
				break;
			}
		}

		// F 키를 누른 경우
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_F))
		{
			if (m_bItemBoxOpen) { break; }

			if (m_wpSurvivor.lock()->IsSkillValid(ESkillType::SECOND))
			{
				break;
			}
		}

		// E 키를 누른 경우
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_E))
		{
			if (m_bItemBoxOpen) { break; }

			if (m_wpSurvivor.lock()->IsSkillValid(ESkillType::THIRD))
			{
				m_eSurvivorState = ESurvivorState::SKILL_03_BEGIN;
				break;
			}
		}

		// Q 키를 누른 경우
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_Q))
		{
			if (m_bItemBoxOpen) { break; }

			if (m_wpSurvivor.lock()->IsSkillValid(ESkillType::FOURTH))
			{
				m_wpCameraComponent.lock()->SetDelayLerpFOVTo(80.0f, 0.5f, 6.5f, true);
				m_eSurvivorState = ESurvivorState::SKILL_04_BEGIN;
				break;
			}
		}

		// CAPSLOCK 키를 누른 경우
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_CAPSLOCK))
		{
			if (shared_ptr<CItemBox> spItemBox = m_wpSurvivor.lock()->GetItemBox())
			{
				if (!spItemBox->IsOpened())
				{
					// m_wpInputComponent.lock()->LockCursor(false);
					m_wpCameraComponent.lock()->LockCamera(true);
					
					if (spItemBox->IsFirstOpened())
					{
						m_wpSurvivor.lock()->AddCurExp(3.5f);
					}
					
					spItemBox->OpenItemBox();
					m_bItemBoxOpen = true;
				}
				else
				{
					// m_wpInputComponent.lock()->LockCursor(true);
					m_wpCameraComponent.lock()->LockCamera(false);
					spItemBox->CloseItemBox();
					m_bItemBoxOpen = false;
				}
				break;
			}

			if (shared_ptr<CWildAnimal> spWildAnimal = m_wpSurvivor.lock()->GetWildAnimal())
			{
				if (!spWildAnimal->IsOpened())
				{
					// m_wpInputComponent.lock()->LockCursor(false);

					if (spWildAnimal->IsFirstOpened())
					{
						m_wpSurvivor.lock()->AddCurExp(3.5f);
					}

					m_wpCameraComponent.lock()->LockCamera(true);
					spWildAnimal->OpenItemBox();
					m_bItemBoxOpen = true;
				}
				else
				{
					// m_wpInputComponent.lock()->LockCursor(true);
					m_wpCameraComponent.lock()->LockCamera(false);
					spWildAnimal->CloseItemBox();
					m_bItemBoxOpen = false;
				}
				break;
			}

			/*
			switch (m_wpSurvivor.lock()->GetCurCollectibleType())
			{
			case ECollectibleType::STONE:	m_eSurvivorState = ESurvivorState::COLLECT_STONE;		break;
			case ECollectibleType::BRANCH:	m_eSurvivorState = ESurvivorState::COLLECT_WOOD;		break;
			case ECollectibleType::WATER:	m_eSurvivorState = ESurvivorState::COLLECT_WATER;		break;
			case ECollectibleType::POTATO:	m_eSurvivorState = ESurvivorState::COLLECT_WOOD;		break;
			}

			switch (m_wpSurvivor.lock()->GetCurConsoleType())
			{
			case EConsoleType::HYPERLOOP:
			case EConsoleType::SECURITY_CONSOLE:	m_eSurvivorState = ESurvivorState::OPERATE;	break;
			}
			*/
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
		// 1 ~ 8번 키를 누른 경우
		EatItem();

		// 방향 키를 누르지 않은 경우
		if (!m_wpInputComponent.lock()->IsKeyPressed(DIK_W)
			&& !m_wpInputComponent.lock()->IsKeyPressed(DIK_S)
			&& !m_wpInputComponent.lock()->IsKeyPressed(DIK_D)
			&& !m_wpInputComponent.lock()->IsKeyPressed(DIK_A))
		{
			m_eSurvivorState = ESurvivorState::WAIT;
			break;
		}

		// 좌클릭을 누른 경우
		if (m_wpInputComponent.lock()->IsMouseDown(EMouseActionType::LEFT_BUTTON))
		{
			if (m_bItemBoxOpen) { break; }

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

		// SHIFT 키를 누른 경우
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_LSHIFT))
		{
			if (m_wpSurvivor.lock()->IsSkillValid(ESkillType::FIRST))
			{
				m_eSurvivorState = ESurvivorState::SKILL_01;
				break;
			}
		}

		// F 키를 누른 경우
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_F))
		{
			if (m_wpSurvivor.lock()->IsSkillValid(ESkillType::SECOND))
			{
				break;
			}
		}

		// E 키를 누른 경우
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_E))
		{
			if (m_wpSurvivor.lock()->IsSkillValid(ESkillType::THIRD))
			{
				m_eSurvivorState = ESurvivorState::SKILL_03_BEGIN;
				break;
			}
		}

		// Q 키를 누른 경우
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_Q))
		{
			if (m_wpSurvivor.lock()->IsSkillValid(ESkillType::FOURTH))
			{
				m_wpCameraComponent.lock()->SetDelayLerpFOVTo(80.0f, 0.5f, 6.5f, true);
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
		// 1 ~ 8번 키를 누른 경우
		EatItem();

		// 1번 키를 누른 경우
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_LSHIFT))
		{
			if (m_wpSurvivor.lock()->IsSkillValid(ESkillType::FIRST))
			{
				m_eSurvivorState = ESurvivorState::SKILL_01;
				break;
			}
		}

		// 2번 키를 누른 경우
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_F))
		{
			if (m_wpSurvivor.lock()->IsSkillValid(ESkillType::SECOND))
			{
				break;
			}
		}

		// 3번 키를 누른 경우
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_E))
		{
			if (m_wpSurvivor.lock()->IsSkillValid(ESkillType::THIRD))
			{
				m_eSurvivorState = ESurvivorState::SKILL_03_BEGIN;
				break;
			}
		}

		// 4번 키를 누른 경우
		if (m_wpInputComponent.lock()->IsKeyDown(DIK_Q))
		{
			if (m_wpSurvivor.lock()->IsSkillValid(ESkillType::FOURTH))
			{
				m_wpCameraComponent.lock()->SetDelayLerpFOVTo(80.0f, 0.5f, 6.5f, true);
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
	case Editor::ESurvivorState::SKILL_02:
	case Editor::ESurvivorState::SKILL_03_BEGIN:
	case Editor::ESurvivorState::SKILL_03:
	case Editor::ESurvivorState::SKILL_03_END:
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

	case Editor::ESurvivorState::SKILL_04_BEGIN:
	case Editor::ESurvivorState::SKILL_04:
	{
		// 체력이 0보다 작은 경우
		if (m_wpSurvivor.lock()->GetCurHP() <= 0)
		{
			m_eSurvivorState = ESurvivorState::DEATH;
			break;
		}

		// 4번 키를 뗀 경우
		if (m_wpInputComponent.lock()->IsKeyUp(DIK_Q))
		{
			m_eSurvivorState = ESurvivorState::SKILL_04_END;
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
		m_fSumCraftMetalSeconds += _fDeltaSeconds;

		if (m_fSumCraftMetalSeconds >= 2.0f)
		{
			m_fSumCraftMetalSeconds = 0.0f;
			m_wpSurvivor.lock()->GetInventory()->CraftItem();

			m_wpSurvivor.lock()->GetInventory()->CheckItemBuildOrder();

			m_wpSurvivor.lock()->AddCurExp(20.0f);
			m_eSurvivorState = ESurvivorState::WAIT;
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
		break;

	case Editor::ESurvivorState::REST_BEGIN:
		break;

	case Editor::ESurvivorState::REST:
	{
		// 1 ~ 8번 키를 누른 경우
		EatItem();

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
		break;
	}
}

void Editor::CHyunwooStateComponent::EatItem()
{
	if (m_wpInputComponent.lock()->IsKeyDown(DIK_1)) { m_wpSurvivor.lock()->GetInventory()->EatItem(0); }
	if (m_wpInputComponent.lock()->IsKeyDown(DIK_2)) { m_wpSurvivor.lock()->GetInventory()->EatItem(1); }
	if (m_wpInputComponent.lock()->IsKeyDown(DIK_3)) { m_wpSurvivor.lock()->GetInventory()->EatItem(2); }
	if (m_wpInputComponent.lock()->IsKeyDown(DIK_4)) { m_wpSurvivor.lock()->GetInventory()->EatItem(3); }
	if (m_wpInputComponent.lock()->IsKeyDown(DIK_5)) { m_wpSurvivor.lock()->GetInventory()->EatItem(4); }
	if (m_wpInputComponent.lock()->IsKeyDown(DIK_6)) { m_wpSurvivor.lock()->GetInventory()->EatItem(5); }
	if (m_wpInputComponent.lock()->IsKeyDown(DIK_7)) { m_wpSurvivor.lock()->GetInventory()->EatItem(6); }
	if (m_wpInputComponent.lock()->IsKeyDown(DIK_8)) { m_wpSurvivor.lock()->GetInventory()->EatItem(7); }
	if (m_wpInputComponent.lock()->IsKeyDown(DIK_9)) { m_wpSurvivor.lock()->GetInventory()->EatItem(8); }
	if (m_wpInputComponent.lock()->IsKeyDown(DIK_0)) { m_wpSurvivor.lock()->GetInventory()->EatItem(9); }
}

void Editor::CHyunwooStateComponent::OnAnimEnter(uint32 _iAnimState, float _fRatio)
{
	switch (static_cast<ESurvivorAnimState>(_iAnimState))
	{
	case ESurvivorAnimState::ATTACK_01:
		break;

	case ESurvivorAnimState::ATTACK_02:
		break;

	case ESurvivorAnimState::SKILL_04_END:
		m_wpCameraComponent.lock()->SetDelayLerpFOVTo(60.0f, 0.28f, 1.0f);
		break;
	}
}

void Editor::CHyunwooStateComponent::OnAnimStay(uint32 _iAnimState, float _fRatio)
{
}

void Editor::CHyunwooStateComponent::OnAnimExit(uint32 _iAnimState, float _fRatio)
{
	switch (static_cast<ESurvivorAnimState>(_iAnimState))
	{
	case ESurvivorAnimState::SKILL_03_BEGIN:
		m_eSurvivorState = ESurvivorState::WAIT;
		break;

	case ESurvivorAnimState::ARRIVE:
	case ESurvivorAnimState::ATTACK_01:
	case ESurvivorAnimState::ATTACK_02:
	case ESurvivorAnimState::SKILL_01:
	case ESurvivorAnimState::SKILL_02:
	case ESurvivorAnimState::SKILL_03:
	case ESurvivorAnimState::SKILL_03_END:
	case ESurvivorAnimState::SKILL_04_END:
	case ESurvivorAnimState::REST_END:
		m_eSurvivorState = ESurvivorState::WAIT;
		break;

	case ESurvivorAnimState::SKILL_04_BEGIN:
		m_eSurvivorState = ESurvivorState::SKILL_04;
		break;

	case ESurvivorAnimState::SKILL_04:
		m_eSurvivorState = ESurvivorState::SKILL_04_END;
		break;

	case ESurvivorAnimState::REST_BEGIN:
		m_eSurvivorState = ESurvivorState::REST;
		break;

	default:
		break;
	}
}
